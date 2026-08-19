// 3D / physics-related binary compat shims. Omitted from Guidot API builds
// where the corresponding generated types are stripped.

using System;
using System.ComponentModel;

namespace Godot;

#pragma warning disable CS1734 // XML comment on 'X' has a paramref tag for 'Y', but there is no parameter by that name.
#pragma warning disable IDE0040 // Add accessibility modifiers.

partial class Geometry3D
{
    /// <inheritdoc cref="SegmentIntersectsConvex(Vector3, Vector3, Godot.Collections.Array{Plane})"/>
    [EditorBrowsable(EditorBrowsableState.Never)]
    public static Vector3[] SegmentIntersectsConvex(Vector3 from, Vector3 to, Godot.Collections.Array planes)
    {
        return SegmentIntersectsConvex(from, to, new Godot.Collections.Array<Plane>(planes));
    }
}

partial class ImporterMesh
{
    /// <inheritdoc cref="AddSurface(Mesh.PrimitiveType, Godot.Collections.Array, Godot.Collections.Array{Godot.Collections.Array}, Godot.Collections.Dictionary, Material, string, ulong)"/>
    [EditorBrowsable(EditorBrowsableState.Never)]
    public void AddSurface(Mesh.PrimitiveType primitive, Godot.Collections.Array arrays, Godot.Collections.Array<Godot.Collections.Array> blendShapes, Godot.Collections.Dictionary lods, Material material, string name, uint flags)
    {
        AddSurface(primitive, arrays, blendShapes, lods, material, name, (ulong)flags);
    }
}

partial class MeshInstance3D
{
    /// <inheritdoc cref="CreateMultipleConvexCollisions(MeshConvexDecompositionSettings)"/>
    [EditorBrowsable(EditorBrowsableState.Never)]
    public void CreateMultipleConvexCollisions()
    {
        CreateMultipleConvexCollisions(settings: null);
    }
}

partial class Node3D
{
    /// <inheritdoc cref="LookAt(Vector3, Nullable{Vector3}, bool)"/>
    [EditorBrowsable(EditorBrowsableState.Never)]
    public void LookAt(Vector3 target, Nullable<Vector3> up)
    {
        LookAt(target, up, useModelFront: false);
    }

    /// <inheritdoc cref="LookAtFromPosition(Vector3, Vector3, Nullable{Vector3}, bool)"/>
    [EditorBrowsable(EditorBrowsableState.Never)]
    public void LookAtFromPosition(Vector3 position, Vector3 target, Nullable<Vector3> up)
    {
        LookAtFromPosition(position, target, up, useModelFront: false);
    }
}

#pragma warning restore CS1734
