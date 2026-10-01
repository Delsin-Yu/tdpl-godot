using System;
using System.Runtime.InteropServices;
using Godot.NativeInterop;

namespace Godot.Bridge
{
    internal static class GCHandleBridge
    {
        [UnmanagedCallersOnly]
        internal static void FreeGCHandle(IntPtr gcHandlePtr)
        {
            try
            {
                CustomGCHandle.Free(GCHandle.FromIntPtr(gcHandlePtr));
            }
            catch (Exception e)
            {
                ExceptionUtils.LogException(e);
            }
        }

        // Returns true if the handle's target is still alive, i.e. has not been
        // garbage-collected. This only reads the target, it never resurrects it, and it does
        // not allocate, so it is safe to call while native locks are held. Used before
        // handing out a new reference to a cached resource (GH-83762).
        [UnmanagedCallersOnly]
        internal static godot_bool CheckGCHandle(IntPtr gcHandlePtr)
        {
            try
            {
                return (GCHandle.FromIntPtr(gcHandlePtr).Target is not null).ToGodotBool();
            }
            catch (Exception e)
            {
                ExceptionUtils.LogException(e);
                return godot_bool.False;
            }
        }

        // Returns true, if releasing the provided handle is necessary for assembly unloading to succeed.
        // This check is not perfect and only intended to prevent things in GodotTools from being reloaded.
        [UnmanagedCallersOnly]
        internal static godot_bool GCHandleIsTargetCollectible(IntPtr gcHandlePtr)
        {
            try
            {
                var target = GCHandle.FromIntPtr(gcHandlePtr).Target;

                if (target is Delegate @delegate)
                    return DelegateUtils.IsDelegateCollectible(@delegate).ToGodotBool();

                return target.GetType().IsCollectible.ToGodotBool();
            }
            catch (Exception e)
            {
                ExceptionUtils.LogException(e);
                return godot_bool.True;
            }
        }
    }
}
