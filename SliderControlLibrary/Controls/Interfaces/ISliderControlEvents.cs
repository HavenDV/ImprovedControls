namespace T3000Controls
{
    using System;
    using System.Runtime.InteropServices;

    [Guid("F26F3F9A-BC68-4B1C-B0D5-3AE75DB82795")]
    [InterfaceType(ComInterfaceType.InterfaceIsIDispatch)]
    public interface ISliderControlEvents
    {
        event Action<object, SliderEventArgs> CurrentValueChanged;
    }
}
