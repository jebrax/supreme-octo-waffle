#include <glade/render/ShaderProgram.h>
#include <glade/render/Drawable.h>
#include <glade/render/meshes/Square.h>
#include <glade/render/meshes/DynamicMesh.h>
#include <glade/render/meshes/DynamicMeshGenerator.h>
#include <glade/util/Path.h>
#include <thatworld/ResourceManager.h>
#include <thatworld/blocks/Terrain.h>

extern Thatworld::ResourceManager *game_resource_manager;

Terrain::Terrain():
  view(NULL),
  initialized(false)
{
  setName("An object");
}

Terrain::~Terrain()
{
  if (view) {
    delete view;
    view = NULL;
  }
}

void Terrain::initialize()
{
  if (!initialized ) {
    std::shared_ptr<ShaderProgram> program =
      game_resource_manager->getShaderProgram(
        "lit_shape.vertex.glsl",
        "lit_shape.fragment.glsl"
      );

    //view = new Drawable(game_resource_manager->getMesh(Glade::ResourceManager::MESH_SQUARE), program);
    
    std::shared_ptr<Glade::Mesh> mesh(new DynamicMesh());
    DynamicMeshGenerator generator;
    generator.generate(*((DynamicMesh*) mesh.get()));

    view = new Drawable(mesh, program);

    view->setUniform("uMaterialAmbient",   Vector4f(0.1f, 0.8f, 0.3f, 1.0f));
    view->setUniform("uMaterialDiffuse",   Vector4f(0.1f, 0.8f, 0.3f, 1.0f));
    view->setUniform("uMaterialSpecular",  Vector4f(1.0f, 1.0f, 1.0f, 1.0f));
    view->setUniform("uMaterialShininess", 128.0f);

    addDrawable(view);
    initialized = true;
  }
}
