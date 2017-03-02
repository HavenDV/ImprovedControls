namespace T3000Controls
{
    using System.Windows.Forms;
    using System.Runtime.InteropServices;

    public partial class SetPointsControl : UserControl
    {
        public SetPointsControl()
        {
            InitializeComponent();
        }

        [ComRegisterFunction()]
        public static void RegisterClass(string key) => ComUtilities.RegisterControlClass(key);

        [ComUnregisterFunction()]
        public static void UnregisterClass(string key) => ComUtilities.UnregisterControlClass(key);
    }
}
