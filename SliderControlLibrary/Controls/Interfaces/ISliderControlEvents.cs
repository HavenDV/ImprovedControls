namespace T3000Controls
{
    using System;
    using System.Runtime.InteropServices;

    [UnmanagedFunctionPointer(CallingConvention.StdCall)]
    public delegate void SliderEventHandler(object sender, SliderEventArgs e);

    [Guid("F26F3F9A-BC68-4B1C-B0D5-3AE75DB82795")]
    [InterfaceType(ComInterfaceType.InterfaceIsIDispatch)]
    public interface ISliderControlEvents
    {
        event SliderEventHandler CurrentValueChanged;
        event SliderEventHandler TopZoneValueChanged;
        event SliderEventHandler BottomZoneValueChanged;
    }
}
