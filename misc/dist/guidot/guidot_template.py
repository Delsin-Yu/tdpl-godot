# Guidot export template: minimal GUI footprint (A+C).
# - A: OpenGL3-only, production/optimize=size, strip leftover game modules
# - C: keep text_server_adv for full font / complex-script shaping
# Advanced GUI stays enabled. C# API is trimmed separately via --guidot-api.

guidot = "yes"
module_mono_enabled = "yes"
no_editor_splash = "yes"
engine_update_check = "no"
graphite = "no"
minimp3_extra_formats = "no"

production = "yes"
optimize = "size_extra"
# Keep deprecated ClassDB entries so GodotSharp MethodBind compatibility hashes resolve.
# (deprecated=no caused NativeMethodBindNotFoundException on Object.is_class at export.)

# Compatibility renderer only (drop Vulkan / D3D12 / Metal + glslang)
vulkan = "no"
d3d12 = "no"
metal = "no"
opengl3 = "yes"
use_volk = "no"
angle = "no"

disable_3d = "yes"
disable_physics_2d = "yes"
disable_navigation_2d = "yes"
# disable_physics_3d / disable_navigation_3d / disable_xr are forced by disable_3d
# Do NOT set disable_advanced_gui

# Text / fonts (GUI) - keep advanced text server (option C)
module_freetype_enabled = "yes"
module_text_server_adv_enabled = "yes"
module_text_server_fb_enabled = "no"
module_msdfgen_enabled = "yes"
brotli = "yes"

# Images
module_jpg_enabled = "yes"
module_webp_enabled = "yes"
module_svg_enabled = "yes"
module_bmp_enabled = "yes"

# Audio
module_ogg_enabled = "yes"
module_vorbis_enabled = "yes"
module_mp3_enabled = "yes"

# Scripting
module_gdscript_enabled = "yes"
module_regex_enabled = "yes"

# No network / multiplayer stack in published GUI apps
module_websocket_enabled = "no"
module_jsonrpc_enabled = "no"
module_mbedtls_enabled = "no"
module_webrtc_enabled = "no"
module_upnp_enabled = "no"
module_multiplayer_enabled = "no"
module_enet_enabled = "no"

# Strip unused game / media / shader modules
module_visual_shader_enabled = "no"
module_theora_enabled = "no"
module_noise_enabled = "no"
module_interactive_music_enabled = "no"
module_tga_enabled = "no"
module_astcenc_enabled = "no"
module_bcdec_enabled = "no"
module_etcpak_enabled = "no"
module_basis_universal_enabled = "no"
module_camera_enabled = "no"
module_csg_enabled = "no"
module_cvtt_enabled = "no"
module_dds_enabled = "no"
module_fbx_enabled = "no"
module_gltf_enabled = "no"
module_gridmap_enabled = "no"
module_hdr_enabled = "no"
module_ktx_enabled = "no"
module_lightmapper_rd_enabled = "no"
module_meshoptimizer_enabled = "no"
module_mobile_vr_enabled = "no"
module_openxr_enabled = "no"
module_raycast_enabled = "no"
module_tinyexr_enabled = "no"
module_vhacd_enabled = "no"
module_webxr_enabled = "no"
module_xatlas_unwrap_enabled = "no"
module_zip_enabled = "no"
