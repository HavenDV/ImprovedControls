namespace T3000Controls
{
    using System;
    using System.Runtime.InteropServices;

    [ComVisible(true)]
    [Guid("7FF2611C-E502-4802-8716-0CC91BE377B8")]
    public class SliderEventArgs : EventArgs
    {
        public float CurrentValue { get; }

        public SliderEventArgs(float value)
        {
            CurrentValue = value;
        }
    }
}
