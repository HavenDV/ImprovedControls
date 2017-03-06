namespace T3000Controls
{
    using System;
    using System.Windows.Forms;
    using System.Runtime.InteropServices;
    using System.ComponentModel;

    [Guid("A7CFC298-FE4E-4819-B868-2C014BA244DE")]
    [ClassInterface(ClassInterfaceType.None)]
    public partial class SetPointsControl : UserControl, ISetPointsControl
    {
        #region DesignerProperties

        private float _topValue = 0;
        [Description("Top value"), Category("SetPointsControl")]
        public float TopValue {
            get { return _topValue; }
            set {
                _topValue = value;

                UpdateTopBottomValues();
            }
        }

        private float _bottomValue = 100;
        [Description("Bottom value"), Category("SetPointsControl")]
        public float BottomValue {
            get { return _bottomValue; }
            set {
                _bottomValue = value;

                UpdateTopBottomValues();
            }
        }

        private float _currentValue = 50;
        [Description("Current value"), Category("SetPointsControl")]
        public float CurrentValue {
            get { return _currentValue; }
            set {
                _currentValue = value;
                panel.CurrentValue = value;
                panel2.CurrentValue = value;
            }
        }

        private float _topZoneValue = 33;
        [Description("Top zone value"), Category("Slider")]
        public float TopZoneValue {
            get { return _topZoneValue; }
            set {
                _topZoneValue = value;
                panel.TopZoneValue = value;
                panel2.TopZoneValue = value;

                Invalidate();
            }
        }

        private float _bottomZoneValue = 66;
        [Description("Bottom zone value"), Category("Slider")]
        public float BottomZoneValue {
            get { return _bottomZoneValue; }
            set {
                _bottomZoneValue = value;
                panel.BottomZoneValue = value;
                panel2.BottomZoneValue = value;

                Invalidate();
            }
        }

        #endregion

        public SetPointsControl()
        {
            InitializeComponent();
        }

        public void UpdateTopBottomValues()
        {
            var topValue = TopValue;
            var bottomValue = BottomValue;
            var delta = Math.Abs(TopValue - BottomValue); // % of this
            var multiplier = 0.05F; //5%
            var divider = 10; //to .. , 10, 20, .. , 80, 90, ..
            if (TopValue > BottomValue)
            {
                topValue = SliderUtilities.RoundUp(TopValue, delta, multiplier, divider);
                bottomValue = SliderUtilities.RoundDown(BottomValue, delta, multiplier, divider);
            }
            else
            {
                topValue = SliderUtilities.RoundDown(TopValue, delta, multiplier, divider);
                bottomValue = SliderUtilities.RoundUp(BottomValue, delta, multiplier, divider);
            }

            topValueLabel.Text = topValue.ToString("F1");
            panel.TopValue = topValue;
            panel2.TopValue = topValue;

            bottomValueLabel.Text = bottomValue.ToString("F1");
            panel.BottomValue = bottomValue;
            panel2.BottomValue = bottomValue;
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

        private void panel_CurrentValueChanged(object sender, SliderEventArgs e)
        {
            panel2.CurrentValue = e.Value;
        }

        private void panel_BottomZoneValueChanged(object sender, SliderEventArgs e)
        {
            panel2.BottomZoneValue = e.Value;
        }

        private void panel_TopZoneValueChanged(object sender, SliderEventArgs e)
        {
            panel2.TopZoneValue = e.Value;
        }

        private void slider1BottomValueCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            var enabled = slider1BottomZoneCheckBox.Checked;
            panel.TopZone = enabled;
            slider1BottomZoneCheckBox.Text = enabled ? panel.BottomZoneValue.ToString("F1") : "-";
        }

        private void slider1TopZoneCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            var enabled = slider1TopZoneCheckBox.Checked;
            panel.TopZone = enabled;
            slider1TopZoneCheckBox.Text = enabled ? panel.TopZoneValue.ToString("F1") : "-";
        }
    }
}
