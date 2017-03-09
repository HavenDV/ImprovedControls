namespace T3000Controls.Tests
{
    using System;
    using System.IO;
    using System.Reflection;
    using System.Text.RegularExpressions;
    using NUnit.Framework;

    [TestFixture]
    class ComUtilitiesTests
    {
        /// <summary>
        /// Check registration in registry. After creation 
        /// SliderControlLibrary automatically use regasm.exe
        /// </summary>
        [Test]
        public void IsRegistered()
        {
            var expected = typeof(SliderControl);

            Assert.AreEqual(expected, Type.GetTypeFromProgID("T3000Controls.SliderControl"));
            Assert.AreEqual(expected, Type.GetTypeFromCLSID(new Guid("ABA068FC-6B49-3031-B74A-1C51A3C8833A")));
        }

        [Test]
        public void TypeLib_CompareEvents()
        {
            var currentDirectory = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location);
            var projectDirectory = Directory.GetParent(Directory.GetParent(currentDirectory).FullName).FullName;
            var solutionDirectory = Directory.GetParent(projectDirectory).FullName;
            Directory.SetCurrentDirectory(solutionDirectory);
            var file = $"SliderControlLibrary/bin/Release/SliderControlLibrary.tlb";
            var text = File.ReadAllText(file);
            
            var expected = typeof(ISliderControlEvents).GetMethods().GetLength(0);
            var actual = Regex.Matches(text, "ValueChanged").Count;

            Assert.AreEqual(expected, actual);

            StringAssert.Contains("CurrentValueChanged", text);
            StringAssert.Contains("TopZoneValueChanged", text);
            StringAssert.Contains("BottomZoneValueChanged", text);
            StringAssert.Contains("TopValueChanged", text);
            StringAssert.Contains("BottomValueChanged", text);
        }
    }
}
