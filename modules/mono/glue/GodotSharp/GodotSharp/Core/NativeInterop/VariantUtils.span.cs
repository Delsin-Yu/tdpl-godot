using System;
using System.Runtime.CompilerServices;

namespace Godot.NativeInterop;

public partial class VariantUtils
{
    [MethodImpl(MethodImplOptions.AggressiveInlining | MethodImplOptions.AggressiveOptimization)]
    public static godot_variant CreateFromSpan(in ReadOnlySpan<byte> from) => CreateFromPackedByteArray(from);

    [MethodImpl(MethodImplOptions.AggressiveInlining | MethodImplOptions.AggressiveOptimization)]
    public static godot_variant CreateFromSpan(in ReadOnlySpan<int> from) => CreateFromPackedInt32Array(from);

    [MethodImpl(MethodImplOptions.AggressiveInlining | MethodImplOptions.AggressiveOptimization)]
    public static godot_variant CreateFromSpan(in ReadOnlySpan<long> from) => CreateFromPackedInt64Array(from);

    [MethodImpl(MethodImplOptions.AggressiveInlining | MethodImplOptions.AggressiveOptimization)]
    public static godot_variant CreateFromSpan(in ReadOnlySpan<float> from) => CreateFromPackedFloat32Array(from);

    [MethodImpl(MethodImplOptions.AggressiveInlining | MethodImplOptions.AggressiveOptimization)]
    public static godot_variant CreateFromSpan(in ReadOnlySpan<double> from) => CreateFromPackedFloat64Array(from);

    [MethodImpl(MethodImplOptions.AggressiveInlining | MethodImplOptions.AggressiveOptimization)]
    public static godot_variant CreateFromSpan(in ReadOnlySpan<string> from) => CreateFromPackedStringArray(from);

    [MethodImpl(MethodImplOptions.AggressiveInlining | MethodImplOptions.AggressiveOptimization)]
    public static godot_variant CreateFromSpan(in ReadOnlySpan<Vector2> from) => CreateFromPackedVector2Array(from);

    [MethodImpl(MethodImplOptions.AggressiveInlining | MethodImplOptions.AggressiveOptimization)]
    public static godot_variant CreateFromSpan(in ReadOnlySpan<Vector3> from) => CreateFromPackedVector3Array(from);

    [MethodImpl(MethodImplOptions.AggressiveInlining | MethodImplOptions.AggressiveOptimization)]
    public static godot_variant CreateFromSpan(in ReadOnlySpan<Vector4> from) => CreateFromPackedVector4Array(from);

    [MethodImpl(MethodImplOptions.AggressiveInlining | MethodImplOptions.AggressiveOptimization)]
    public static godot_variant CreateFromSpan(in ReadOnlySpan<Color> from) => CreateFromPackedColorArray(from);

    [MethodImpl(MethodImplOptions.AggressiveInlining | MethodImplOptions.AggressiveOptimization)]
    public static godot_variant CreateFromSpan(in ReadOnlySpan<Rid> from) => CreateFromSystemArrayOfRid(from);

    [MethodImpl(MethodImplOptions.AggressiveInlining | MethodImplOptions.AggressiveOptimization)]
    public static godot_variant CreateFromSpan(in ReadOnlySpan<StringName> from) => CreateFromSystemArrayOfStringName(from);

    [MethodImpl(MethodImplOptions.AggressiveInlining | MethodImplOptions.AggressiveOptimization)]
    public static godot_variant CreateFromSpan(in ReadOnlySpan<NodePath> from) => CreateFromSystemArrayOfNodePath(from);

    [MethodImpl(MethodImplOptions.AggressiveInlining | MethodImplOptions.AggressiveOptimization)]
    public static ReadOnlySpan<byte> ConvertToByteSpan(in godot_variant variant) => ConvertAsPackedByteArrayToSystemArray(variant);

    [MethodImpl(MethodImplOptions.AggressiveInlining | MethodImplOptions.AggressiveOptimization)]
    public static ReadOnlySpan<int> ConvertToIntSpan(in godot_variant variant) => ConvertAsPackedInt32ArrayToSystemArray(variant);

    [MethodImpl(MethodImplOptions.AggressiveInlining | MethodImplOptions.AggressiveOptimization)]
    public static ReadOnlySpan<long> ConvertToLongSpan(in godot_variant variant) => ConvertAsPackedInt64ArrayToSystemArray(variant);

    [MethodImpl(MethodImplOptions.AggressiveInlining | MethodImplOptions.AggressiveOptimization)]
    public static ReadOnlySpan<float> ConvertToFloatSpan(in godot_variant variant) => ConvertAsPackedFloat32ArrayToSystemArray(variant);

    [MethodImpl(MethodImplOptions.AggressiveInlining | MethodImplOptions.AggressiveOptimization)]
    public static ReadOnlySpan<double> ConvertToDoubleSpan(in godot_variant variant) => ConvertAsPackedFloat64ArrayToSystemArray(variant);

    [MethodImpl(MethodImplOptions.AggressiveInlining | MethodImplOptions.AggressiveOptimization)]
    public static ReadOnlySpan<string> ConvertToStringSpan(in godot_variant variant) => ConvertAsPackedStringArrayToSystemArray(variant);

    [MethodImpl(MethodImplOptions.AggressiveInlining | MethodImplOptions.AggressiveOptimization)]
    public static ReadOnlySpan<Vector2> ConvertToVector2Span(in godot_variant variant) => ConvertAsPackedVector2ArrayToSystemArray(variant);

    [MethodImpl(MethodImplOptions.AggressiveInlining | MethodImplOptions.AggressiveOptimization)]
    public static ReadOnlySpan<Vector3> ConvertToVector3Span(in godot_variant variant) => ConvertAsPackedVector3ArrayToSystemArray(variant);

    [MethodImpl(MethodImplOptions.AggressiveInlining | MethodImplOptions.AggressiveOptimization)]
    public static ReadOnlySpan<Vector4> ConvertToVector4Span(in godot_variant variant) => ConvertAsPackedVector4ArrayToSystemArray(variant);

    [MethodImpl(MethodImplOptions.AggressiveInlining | MethodImplOptions.AggressiveOptimization)]
    public static ReadOnlySpan<Color> ConvertToColorSpan(in godot_variant variant) => ConvertAsPackedColorArrayToSystemArray(variant);

    [MethodImpl(MethodImplOptions.AggressiveInlining | MethodImplOptions.AggressiveOptimization)]
    public static ReadOnlySpan<Rid> ConvertToRidSpan(in godot_variant variant) => ConvertToSystemArrayOfRid(variant);

    [MethodImpl(MethodImplOptions.AggressiveInlining | MethodImplOptions.AggressiveOptimization)]
    public static ReadOnlySpan<StringName> ConvertToStringNameSpan(in godot_variant variant) => ConvertToSystemArrayOfStringName(variant);

    [MethodImpl(MethodImplOptions.AggressiveInlining | MethodImplOptions.AggressiveOptimization)]
    public static ReadOnlySpan<NodePath> ConvertToNodePathSpan(in godot_variant variant) => ConvertToSystemArrayOfNodePath(variant);

}
