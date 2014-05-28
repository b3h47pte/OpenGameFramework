#pragma once
#ifndef _MATERIAL_H
#define _MATERIAL_H

/*
 * Materials determine how a mesh gets rendered (i.e. its diffuse color, specular color, etc.). 
 * The goal is to eventually allow for the creation of complex materials like those that can be made
 *  using the UE3/4 material editor.
 */
class Material
{
public:
  Material();
  virtual ~Material();
};

#endif // _MATERIAL_H