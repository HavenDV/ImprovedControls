namespace T3000Controls
{
    using System;
    using System.Windows.Forms;
    using System.Runtime.InteropServices;

    [Guid("8B73FB00-F011-49F3-A3BD-5305E673CA96")]
    [ClassInterface(ClassInterfaceType.None)]
    [ComSourceInterfaces(typeof(IUserCheckBoxEvents))]
    public partial class UserCheckBox : CheckBox, IUserCheckBox
    {
        public UserCheckBox()
        {
            InitializeComponent();
        }

        [ComRegisterFunction()]
        public static void RegisterClass(Type type) => ComUtilities.RegisterControlClass(type);

        [ComUnregisterFunction()]
        public static void UnregisterClass(Type type) => ComUtilities.UnregisterControlClass(type);
    }
}
