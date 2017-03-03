namespace T3000Controls
{
    using System;
    using System.Runtime.InteropServices;

    [ComVisible(true)]
    public class SliderEventArgs : EventArgs
    {
        public float CurrentValue { get; }

        public SliderEventArgs(float value)
        {
            CurrentValue = value;
        }
    }
}
