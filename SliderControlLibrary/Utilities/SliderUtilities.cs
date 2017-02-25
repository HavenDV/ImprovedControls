namespace T3000Controls
{
    using System;

    public static class SliderUtilities
    {
        public static float YToValue(float y, float topValue, float bottomValue, int height)
        {
            var delta = Math.Abs(topValue - bottomValue);
            var oneValue = delta / height;
            var value = y * oneValue;

            return topValue > bottomValue ? (topValue - value) : (topValue + value);
        }

        public static float ValueToY(float value, float topValue, float bottomValue, int height)
        {
            var delta = Math.Abs(topValue - bottomValue);
            var oneValueHeight = height / delta;
            var valueFromTop = topValue > bottomValue ? (value - bottomValue) : (value - topValue);
            var y = valueFromTop*oneValueHeight;

            return topValue > bottomValue ? height - y : y;
        }

        public static float GetOffsetValueForValue(float value, float topValue, float bottomValue)
        {
            if (topValue > bottomValue)
            {
                var prevValue = (float)Math.Floor(topValue / value) * value;

                return topValue - prevValue;
            }

            var nextValue = (float)Math.Ceiling(topValue / value) * value;
            
            return nextValue - topValue;
        }
    }
}
