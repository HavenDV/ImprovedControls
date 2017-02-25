using NUnit.Framework;

namespace T3000Controls.Tests
{
    [TestFixture]
    public class Utilities_Tests
    {
        [Test]
        public void YToValue_Direct()
        {
            //Y from 0 to 100, TopValue = 0, BottomValue = 100, Height = 100
            Assert.AreEqual(0, Utilities.YToValue(0, 0, 100, 100));
            Assert.AreEqual(5, Utilities.YToValue(5, 0, 100, 100));
            Assert.AreEqual(50, Utilities.YToValue(50, 0, 100, 100));
            Assert.AreEqual(95, Utilities.YToValue(95, 0, 100, 100));
            Assert.AreEqual(100, Utilities.YToValue(100, 0, 100, 100));

            //Y from 0 to 200, TopValue = 0, BottomValue = 100, Height = 200
            Assert.AreEqual(0, Utilities.YToValue(0, 0, 100, 200));
            Assert.AreEqual(5, Utilities.YToValue(10, 0, 100, 200));
            Assert.AreEqual(50, Utilities.YToValue(100, 0, 100, 200));
            Assert.AreEqual(95, Utilities.YToValue(190, 0, 100, 200));
            Assert.AreEqual(100, Utilities.YToValue(200, 0, 100, 200));

            //Y from 0 to 100, TopValue = 100, BottomValue = 200, Height = 100
            Assert.AreEqual(100, Utilities.YToValue(0, 100, 200, 100));
            Assert.AreEqual(105, Utilities.YToValue(5, 100, 200, 100));
            Assert.AreEqual(150, Utilities.YToValue(50, 100, 200, 100));
            Assert.AreEqual(195, Utilities.YToValue(95, 100, 200, 100));
            Assert.AreEqual(200, Utilities.YToValue(100, 100, 200, 100));
        }

        [Test]
        public void YToValue_Inverse()
        {
            //Y from 0 to 100, TopValue = 100, BottomValue = 0, Height = 100
            Assert.AreEqual(100, Utilities.YToValue(0, 100, 0, 100));
            Assert.AreEqual(95, Utilities.YToValue(5, 100, 0, 100));
            Assert.AreEqual(50, Utilities.YToValue(50, 100, 0, 100));
            Assert.AreEqual(5, Utilities.YToValue(95, 100, 0, 100));
            Assert.AreEqual(0, Utilities.YToValue(100, 100, 0, 100));

            //Y from 0 to 200, TopValue = 100, BottomValue = 0, Height = 200
            Assert.AreEqual(100, Utilities.YToValue(0, 100, 0, 200));
            Assert.AreEqual(95, Utilities.YToValue(10, 100, 0, 200));
            Assert.AreEqual(50, Utilities.YToValue(100, 100, 0, 200));
            Assert.AreEqual(5, Utilities.YToValue(190, 100, 0, 200));
            Assert.AreEqual(0, Utilities.YToValue(200, 100, 0, 200));

            //Y from 0 to 100, TopValue = 200, BottomValue = 100, Height = 100
            Assert.AreEqual(200, Utilities.YToValue(0, 200, 100, 100));
            Assert.AreEqual(195, Utilities.YToValue(5, 200, 100, 100));
            Assert.AreEqual(150, Utilities.YToValue(50, 200, 100, 100));
            Assert.AreEqual(105, Utilities.YToValue(95, 200, 100, 100));
            Assert.AreEqual(100, Utilities.YToValue(100, 200, 100, 100));
        }

        [Test]
        public void ValueToY_Direct()
        {
            //Value from 0 to 100, TopValue = 0, BottomValue = 100, Height = 100
            Assert.AreEqual(0, Utilities.ValueToY(0, 0, 100, 100));
            Assert.AreEqual(5, Utilities.ValueToY(5, 0, 100, 100));
            Assert.AreEqual(50, Utilities.ValueToY(50, 0, 100, 100));
            Assert.AreEqual(95, Utilities.ValueToY(95, 0, 100, 100));
            Assert.AreEqual(100, Utilities.ValueToY(100, 0, 100, 100));

            //Value from 0 to 100, TopValue = 0, BottomValue = 100, Height = 200
            Assert.AreEqual(0, Utilities.ValueToY(0, 0, 100, 200));
            Assert.AreEqual(10, Utilities.ValueToY(5, 0, 100, 200));
            Assert.AreEqual(100, Utilities.ValueToY(50, 0, 100, 200));
            Assert.AreEqual(190, Utilities.ValueToY(95, 0, 100, 200));
            Assert.AreEqual(200, Utilities.ValueToY(100, 0, 100, 200));

            //Value from 100 to 200, TopValue = 100, BottomValue = 200, Height = 100
            Assert.AreEqual(0, Utilities.ValueToY(100, 100, 200, 100));
            Assert.AreEqual(5, Utilities.ValueToY(105, 100, 200, 100));
            Assert.AreEqual(50, Utilities.ValueToY(150, 100, 200, 100));
            Assert.AreEqual(95, Utilities.ValueToY(195, 100, 200, 100));
            Assert.AreEqual(100, Utilities.ValueToY(200, 100, 200, 100));
        }

        [Test]
        public void ValueToY_Inverse()
        {
            //Value from 0 to 100, TopValue = 100, BottomValue = 0, Height = 100
            Assert.AreEqual(100, Utilities.ValueToY(0, 100, 0, 100));
            Assert.AreEqual(95, Utilities.ValueToY(5, 100, 0, 100));
            Assert.AreEqual(50, Utilities.ValueToY(50, 100, 0, 100));
            Assert.AreEqual(5, Utilities.ValueToY(95, 100, 0, 100));
            Assert.AreEqual(0, Utilities.ValueToY(100, 100, 0, 100));

            //Value from 0 to 100, TopValue = 100, BottomValue = 0, Height = 200
            Assert.AreEqual(190, Utilities.ValueToY(5, 100, 0, 200));
            Assert.AreEqual(100, Utilities.ValueToY(50, 100, 0, 200));
            Assert.AreEqual(10, Utilities.ValueToY(95, 100, 0, 200));
            Assert.AreEqual(0, Utilities.ValueToY(100, 100, 0, 200));

            //Value from 100 to 200, TopValue = 200, BottomValue = 100, Height = 100
            Assert.AreEqual(100, Utilities.ValueToY(100, 200, 100, 100));
            Assert.AreEqual(95, Utilities.ValueToY(105, 200, 100, 100));
            Assert.AreEqual(50, Utilities.ValueToY(150, 200, 100, 100));
            Assert.AreEqual(5, Utilities.ValueToY(195, 200, 100, 100));
            Assert.AreEqual(0, Utilities.ValueToY(200, 200, 100, 100));
        }

        [Test]
        public void GetOffsetForValue_Direct()
        {
            Assert.AreEqual(0, Utilities.GetOffsetValueForValue(5, 0, 100));
            Assert.AreEqual(0, Utilities.GetOffsetValueForValue(5, 100, 200));

            Assert.AreEqual(2, Utilities.GetOffsetValueForValue(5, 3, 100));
            Assert.AreEqual(2, Utilities.GetOffsetValueForValue(5, 103, 200));

            Assert.AreEqual(0, Utilities.GetOffsetValueForValue(10, 0, 100));
            Assert.AreEqual(0, Utilities.GetOffsetValueForValue(10, 100, 200));

            Assert.AreEqual(5, Utilities.GetOffsetValueForValue(10, 5, 100));
            Assert.AreEqual(5, Utilities.GetOffsetValueForValue(10, 105, 200));
        }

        [Test]
        public void GetOffsetForValue_Inserse()
        {
            Assert.AreEqual(0, Utilities.GetOffsetValueForValue(5, 100, 0));
            Assert.AreEqual(0, Utilities.GetOffsetValueForValue(5, 200, 100));

            Assert.AreEqual(2, Utilities.GetOffsetValueForValue(5, 97, 0));
            Assert.AreEqual(2, Utilities.GetOffsetValueForValue(5, 197, 100));

            Assert.AreEqual(0, Utilities.GetOffsetValueForValue(10, 100, 0));
            Assert.AreEqual(0, Utilities.GetOffsetValueForValue(10, 200, 100));

            Assert.AreEqual(5, Utilities.GetOffsetValueForValue(10, 95, 0));
            Assert.AreEqual(5, Utilities.GetOffsetValueForValue(10, 195, 100));
        }
    }
}
