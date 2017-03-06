namespace T3000Controls.Tests
{
    using System;
    using NUnit.Framework;

    [TestFixture]
    public class ComUtilitiesTests
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
            Assert.AreEqual(expected, Type.GetTypeFromProgID("T3000Controls.SliderControl.1"));
        }
    }
}
