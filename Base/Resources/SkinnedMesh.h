#pragma once

#include <memory>

#include "MDX.h"

#include "ResourceManager.h"
#include "GPUTexture.h"
#include "Shader.h"
#include "SkeletalModelInstance.h"

class SkinnedMesh : public Resource {
  public:
	struct MeshEntry {
		int vertices = 0;
		int indices = 0;
		int base_vertex = 0;
		int base_index = 0;

		int material_id = 0;
		mdx::Extent extent;

		bool hd = true;
		mdx::GeosetAnimation* geoset_anim; // can be nullptr, often
		// below vectors are per-instance:
		std::vector<float> geoset_anim_alphas;
		std::vector<glm::vec3> geoset_anim_colors;
		std::vector<float> layer_alphas;
	};

	std::shared_ptr<mdx::MDX> model;

	std::vector<MeshEntry> entries;
	bool has_mesh; // ToDo remove when added support for meshless

	GLuint vao;
	GLuint vertex_buffer;
	GLuint uv_buffer;
	GLuint normal_buffer;
	GLuint tangent_buffer;
	GLuint weight_buffer;
	GLuint index_buffer;
	GLuint instance_buffer;
	GLuint retera_node_buffer;
	GLuint retera_node_buffer_texture;
	GLuint layer_alpha;
	GLuint geoset_color;

	fs::path path;
	int mesh_id;
	std::vector<std::shared_ptr<GPUTexture>> textures;
	std::vector<mdx::Material> materials;
	std::vector<glm::mat4> render_jobs;
	std::vector<const SkeletalModelInstance*> skeletons;
	std::vector<glm::mat4> instance_bone_matrices;

	static constexpr const char* name = "SkinnedMesh";

	explicit SkinnedMesh(const fs::path& path);
	virtual ~SkinnedMesh();

	void render_queue(const SkeletalModelInstance& skeleton);
	void render_color_coded(const SkeletalModelInstance& skeleton, int id);

	void render_opaque_sd();
	void render_opaque_hd();

	void render_transparent_sd(int instance_id);
	void render_transparent_hd(int instance_id);
};