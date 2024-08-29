@echo off
chcp 65001

scons --version
python --version

set BUILD_NAME=tdpl
scons module_bmp_enabled=no module_camera_enabled=no module_csg_enabled=no module_cvtt_enabled=no module_dds_enabled=no module_fbx_enabled=no module_gltf_enabled=no module_gridmap_enabled=no module_hdr_enabled=no module_jsonrpc_enabled=no module_ktx_enabled=no module_lightmapper_rd_enabled=no module_mbedtls_enabled=no module_meshoptimizer_enabled=no minimp3_extra_formats=no module_mobile_vr_enabled=no module_mono_enabled=yes module_raycast_enabled=no graphite=no module_tinyexr_enabled=no module_upnp_enabled=no module_vhacd_enabled=no module_webp_enabled=no module_webrtc_enabled=no module_websocket_enabled=no module_webxr_enabled=no module_xatlas_unwrap_enabled=no module_zip_enabled=no p=windows debug_symbols=yes deprecated=no no_editor_splash=yes engine_update_check=no arch=x86_64 target=template_release
pause
