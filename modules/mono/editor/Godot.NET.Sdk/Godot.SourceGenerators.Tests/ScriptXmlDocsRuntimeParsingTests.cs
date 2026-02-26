using Godot.Bridge;
using Godot.NativeInterop;
using Xunit;

namespace Godot.SourceGenerators.Tests;

public class ScriptXmlDocsRuntimeParsingTests
{
    [Fact]
    public void RuntimeXmlDocsPlaceholder()
    {
        // Runtime XML docs parsing lives in GodotSharp runtime (ScriptManagerBridge).
        // Dedicated integration tests will be added as part of runtime test harness work.
        Assert.True(typeof(ScriptManagerBridge) != null);
        Assert.True(typeof(godot_bool) != null);
    }
}
