#include <taihen.h>
#include <vitasdk.h>

static SceUID g_hooks[2];
uint32_t text_addr, text_size, data_addr, data_size;

void _start() __attribute__ ((weak, alias ("module_start")));

static tai_hook_ref_t ref_hook0;
static int sceAppMgrAcquireBgmPort_patched(void)
{
	return 0;
}

static tai_hook_ref_t ref_hook1;
static int sceAppMgrReleaseBgmPort_patched(void)
{
	return 0;
}

int module_start(SceSize argc, const void *args)
{
  g_hooks[0] = taiHookFunctionImport(&ref_hook0,
	TAI_MAIN_MODULE,
	0x8AF17416, //SceAppMgr
	0xAFCEAB96,
	sceAppMgrAcquireBgmPort_patched);
  g_hooks[0] = taiHookFunctionImport(&ref_hook0,
	TAI_MAIN_MODULE,
	0x8AF17416, //SceAppMgr
	0xF3717E37,
	sceAppMgrReleaseBgmPort_patched);

  return SCE_KERNEL_START_SUCCESS;
}

int module_stop(SceSize argc, const void *args) 
{
	if (g_hooks[0] >= 0) taiHookRelease(g_hooks[0], ref_hook0);
	if (g_hooks[1] >= 0) taiHookRelease(g_hooks[1], ref_hook1);
  return SCE_KERNEL_STOP_SUCCESS;
}
