#nullable enable
using System;
using System.Collections.Generic;
using Godot.NativeInterop;

namespace Godot.Bridge;

public delegate bool InvokeGodotClassStaticMethodDelegate(in godot_string_name method, NativeVariantPtrArgs args, out godot_variant ret);

public record struct ScriptTypeInfo(
    Dictionary<int, ScriptConstructorInfo> ConstructorInfos,
    InvokeGodotClassStaticMethodDelegate? CallStaticMethodDelegate,
    MethodInfo[] MethodList,
    MethodInfo[] SignalList,
    PropertyInfo[] PropertyList,
    RpcMethodInfo[] RpcMethodList,
    Dictionary<StringName, Variant> DefaultValuesDictionary);

public record struct ScriptConstructorInfo(Action<IntPtr, object?[]> Constructor, Type[] ParameterTypes);
