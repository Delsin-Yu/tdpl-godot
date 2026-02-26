using System;
using System.IO;
using Godot.Bridge;
using Xunit;

namespace Godot.SourceGenerators.Tests;

public class XmlDocumentationBbCodeTests
{
    [Fact]
    public void ParseSummaryAndRemarks_WithSeeAndParamRef()
    {
        string xml = """
            <?xml version=\"1.0\"?>
            <doc>
              <members>
                <member name=\"T:Game.MyType\">
                  <summary>
                    Hello <see cref=\"T:System.String\"/>.
                  </summary>
                  <remarks>
                    Use <paramref name=\"value\"/>.
                  </remarks>
                </member>
              </members>
            </doc>
            """;

        string file = WriteTempXml(xml);
        var members = XmlDocumentationBbCode.LoadMembersFromFile(file);

        string? summary = XmlDocumentationBbCode.TryGetTagBbCode(members, typeof(DummyType), "T:Game.MyType", "summary");
        string? remarks = XmlDocumentationBbCode.TryGetTagBbCode(members, typeof(DummyType), "T:Game.MyType", "remarks");

        Assert.Equal("Hello [code]T:System.String[/code].", summary);
        Assert.Equal("Use [param value].", remarks);
    }

    [Fact]
    public void Inheritdoc_WithCref_ResolvesSummary()
    {
        string xml = """
            <?xml version=\"1.0\"?>
            <doc>
              <members>
                <member name=\"T:Game.BaseType\">
                  <summary>Base docs.</summary>
                </member>
                <member name=\"T:Game.ChildType\">
                  <inheritdoc cref=\"T:Game.BaseType\"/>
                </member>
              </members>
            </doc>
            """;

        string file = WriteTempXml(xml);
        var members = XmlDocumentationBbCode.LoadMembersFromFile(file);

        string? summary = XmlDocumentationBbCode.TryGetTagBbCode(members, typeof(DummyType), "T:Game.ChildType", "summary");

        Assert.Equal("Base docs.", summary);
    }

    [Fact]
    public void MissingXmlFile_Throws()
    {
        string missingFile = Path.Combine(Path.GetTempPath(), Guid.NewGuid() + ".xml");
      FileNotFoundException ex = Assert.Throws<FileNotFoundException>(() =>
      {
        _ = XmlDocumentationBbCode.LoadMembersFromFile(missingFile);
      });
      Assert.Equal(missingFile, ex.FileName);
    }

    private static string WriteTempXml(string content)
    {
        string path = Path.Combine(Path.GetTempPath(), Guid.NewGuid() + ".xml");
        File.WriteAllText(path, content);
        return path;
    }

    private sealed class DummyType
    {
    }
}
