# Guidot editor profile: keep 3D native code so the editor links and can generate C# glue.
# Do NOT set disable_3d / disable_physics_* / disable_navigation_* / disable_advanced_gui here.

guidot = "yes"
module_mono_enabled = "yes"
no_editor_splash = "yes"
engine_update_check = "no"
graphite = "no"
minimp3_extra_formats = "no"

# Text / fonts (GUI)
module_freetype_enabled = "yes"
module_text_server_adv_enabled = "yes"
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

# Editor LSP / GDScript language server
module_gdscript_enabled = "yes"
module_websocket_enabled = "yes"
module_jsonrpc_enabled = "yes"
module_regex_enabled = "yes"

# Strip unused game / 3D-pipeline modules (editor still compiles scene/3d)
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
module_upnp_enabled = "no"
module_vhacd_enabled = "no"
module_webrtc_enabled = "no"
module_webxr_enabled = "no"
module_xatlas_unwrap_enabled = "no"
module_zip_enabled = "no"
module_mbedtls_enabled = "no"
