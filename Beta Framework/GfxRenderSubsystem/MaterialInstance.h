#pragma once
#ifndef _MATERIALINST_H
#define _MATERIALINST_H

/*
 * A material gets stored and is available for use by ALL meshes/renderables in the scene.
 * However, sometimes a material must be modified in some way during runtime and hence each
 * renderable instance should have a material instance made which is used in place of the
 * old material.
 */
class MaterialInstance
{
public:
  MaterialInstance();
  virtual ~MaterialInstance();
};

#endif // _MATERIALINST_H

