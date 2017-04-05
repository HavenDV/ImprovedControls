namespace T3000Controls
{
    using System;
    using System.Runtime.InteropServices;

    [InterfaceType(ComInterfaceType.InterfaceIsIDispatch)]
    public interface IUserCheckBoxEvents
    {
        #region Check box events

        [DispId(-620)]
        void CheckedChanged(object sender, EventArgs e);

        #endregion
    }
}
