namespace T3000Controls
{
    using System;
    using System.Runtime.InteropServices;

    [ComVisible(false)]
    public delegate void ValueChangedEventHandler(object sender, float newValue);

    [InterfaceType(ComInterfaceType.InterfaceIsIDispatch)]
    public interface ISliderControlEvents
    {
        [DispId(1)]
        void TopZoneValueChanged(object sender, float newValue);

        [DispId(2)]
        void BottomZoneValueChanged(object sender, float newValue);

        [DispId(3)]
        void CurrentValueChanged(object sender, float newValue);

        [DispId(4)]
        void TopValueChanged(object sender, float newValue);

        [DispId(5)]
        void BottomValueChanged(object sender, float newValue);

        [DispId(-610)]
        void Click(object sender, EventArgs e);
    }
}
