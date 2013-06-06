#include "GfxUtility.h"
#include "MeshRenderable.h"
#include "WFile.h"

#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;

/*
 * Reads in the OBJ file and creates a MeshRenderable. 
 */
IRenderable* ReadOBJFile(std::string inFile) {
	static float DEFAULT_TEX_COORD[2] = {0.f, 0.f};
	WFile file(inFile);

	MeshRenderable* newMesh = new MeshRenderable();
	if (!newMesh) return NULL;

	vector<string> allObjText;
	file.ReadAllTextData(allObjText);

	/*
	 * Parse OBJ file data.
	 * Support the following definitions:
	 *		- v, vt, vn
	 *		- f
	 */ 
	int lineNum = 0;
	int vertCount = 0;
	for (auto& s : allObjText) {
		// Each command will be in the format: DEFINITION ### ### ###
		// First extract the definition
		istringstream iss(s);
		vector<string> lineData;
		copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter<vector<string> >(lineData));

		if (lineData.size() == 0) 
			continue;

		vector<float*> vertPos;
		vector<float*> vertNorm;
		vector<float*> vertTex;

		// Determine what the definition is and act appropriately
		if (lineData[0][0] == '#')
			continue;

		if (lineData[0].compare("v") == 0) {
			// Vertex Position
			// Only support vertices that supply x, y, z. Anything less is an error. Anything more will be ignored.
			if (lineData.size() < 4) {
				cout << "ReadOBJFile Error: Input 'v' definition has less than 4 arguments on line: " << lineNum << endl;
				return NULL;
			}
			float p[4] = {atof(lineData[1].c_str()), atof(lineData[2].c_str()), atof(lineData[3].c_str()), 1.f };
			vertPos.push_back(p);
		} else if (lineData[0].compare("vt") == 0) {
			// Vertex Texture Coordinate
			if (lineData.size() < 3) {
				cout << "ReadOBJFile Error: Input 'vt' definition has less than 3 arguments on line: " << lineNum << endl;
				return NULL;
			}
			float t[2] = {atof(lineData[1].c_str()), atof(lineData[2].c_str())};
			vertTex.push_back(t);
		} else if (lineData[0].compare("vn") == 0) {
			// Vertex Normal
			if (lineData.size() < 4) {
				cout << "ReadOBJFile Error: Input 'vn' definition has less than 4 arguments on line: " << lineNum << endl;
				return NULL; 
			}
			float n[4] = {atof(lineData[1].c_str()), atof(lineData[2].c_str()), atof(lineData[3].c_str()), 0.f };
			vertNorm.push_back(n);
		} else if (lineData[0].compare("f") == 0) { 
			// Face
			// Only triangles are supported. Having polygons will cause an error to be created and no mesh to be made.
			// All vertices MUST include normal data.
			if (lineData.size() < 4) {
				cout << "ReadOBJFile Error: Input 'f' definition has less than 4 arguments on line: " << lineNum << endl;
				return NULL;
			}
			// Create new vertices in the mesh as we read in the faces (feel free to use the extra memory here(?) because it'll eventually be cleared anyways)
			// Probably should find an easier/more efficient way to do this without using so much excessive memory but this will work for now
			for (int i = 1; i <= 3; ++i) {
				size_t firstSlash = lineData[i].find('/');
				size_t secondSlash = lineData[i].find('/', firstSlash + 1);

				// Parse position data
				string sPos = lineData[i].substr(0, firstSlash);
				int pos = atoi(sPos.c_str());
				newMesh->AddVertexPosition(vertPos[pos]);

				// Read in tex data if it exists.
				if (firstSlash + 1 != secondSlash) {
					string sTex = lineData[i].substr(firstSlash + 1, secondSlash);
					int tex = atoi(sTex.c_str());
					newMesh->AddVertexTex(vertTex[tex]);

				} else { // Tex Data does not exist -- Use a default (0, 0) filler
					newMesh->AddVertexTex(DEFAULT_TEX_COORD);
				}

				// Read in normal data
				string sNorm = lineData[i].substr(secondSlash+1);
				int norm = atoi(sNorm.c_str());
				newMesh->AddVertexNormal(vertNorm[norm]);

				newMesh->AddTriangleIndex(vertCount);
				++vertCount;
			}
		}
		// Ignore all other definitions (o, g, etc.) as they are not supported
		++lineNum;
	}

	return newMesh;
}