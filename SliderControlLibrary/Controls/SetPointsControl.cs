using System;

namespace T3000Controls
{
    using System.Windows.Forms;
    using System.Runtime.InteropServices;

    [Guid("A7CFC298-FE4E-4819-B868-2C014BA244DE")]
    [ClassInterface(ClassInterfaceType.None)]
    public partial class SetPointsControl : UserControl, ISetPointsControl
    {
        public SetPointsControl()
        {
            InitializeComponent();
        }

        [ComRegisterFunction()]
        public static void RegisterClass(string key) => ComUtilities.RegisterControlClass(key);

        [ComUnregisterFunction()]
        public static void UnregisterClass(string key) => ComUtilities.UnregisterControlClass(key);

        private void panel1TwoSliderModeCheckBox_CheckedChanged(object sender, System.EventArgs e)
        {
            panel.TwoSliderMode = panel1TwoSliderModeCheckBox.Checked;

            panel.CurrentValue += new Random().Next() % 10 - 5;
        }

        private void panel_CurrentValueChanged(object sender, EventArgs e)
        {
            panel2.CurrentValue = panel.CurrentValue;
        }
    }
}
