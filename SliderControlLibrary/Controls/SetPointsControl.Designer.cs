namespace T3000Controls
{
    partial class SetPointsControl
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Component Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.panel1TwoSliderModeCheckBox = new System.Windows.Forms.CheckBox();
            this.topValueLabel = new System.Windows.Forms.Label();
            this.bottomValueLabel = new System.Windows.Forms.Label();
            this.panel2 = new T3000Controls.SliderControl();
            this.panel = new T3000Controls.SliderControl();
            this.SuspendLayout();
            // 
            // panel1TwoSliderModeCheckBox
            // 
            this.panel1TwoSliderModeCheckBox.Location = new System.Drawing.Point(200, 0);
            this.panel1TwoSliderModeCheckBox.Name = "panel1TwoSliderModeCheckBox";
            this.panel1TwoSliderModeCheckBox.Size = new System.Drawing.Size(100, 20);
            this.panel1TwoSliderModeCheckBox.TabIndex = 5;
            this.panel1TwoSliderModeCheckBox.Text = "TwoSliderMode";
            this.panel1TwoSliderModeCheckBox.UseVisualStyleBackColor = true;
            this.panel1TwoSliderModeCheckBox.CheckedChanged += new System.EventHandler(this.panel1TwoSliderModeCheckBox_CheckedChanged);
            // 
            // topValueLabel
            // 
            this.topValueLabel.Location = new System.Drawing.Point(120, 0);
            this.topValueLabel.Name = "topValueLabel";
            this.topValueLabel.Size = new System.Drawing.Size(0, 20);
            this.topValueLabel.TabIndex = 6;
            // 
            // bottomValueLabel
            // 
            this.bottomValueLabel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.bottomValueLabel.Location = new System.Drawing.Point(120, 480);
            this.bottomValueLabel.Name = "bottomValueLabel";
            this.bottomValueLabel.Size = new System.Drawing.Size(0, 20);
            this.bottomValueLabel.TabIndex = 7;
            // 
            // panel2
            // 
            this.panel2.AdditionalText = " F";
            this.panel2.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
            this.panel2.BackColor = System.Drawing.Color.Transparent;
            this.panel2.BackgroundWidth = 20;
            this.panel2.BorderColor = System.Drawing.Color.Black;
            this.panel2.BottomValue = -100F;
            this.panel2.BottomZone = true;
            this.panel2.BottomZoneColor = System.Drawing.Color.Red;
            this.panel2.BottomZoneValue = -50F;
            this.panel2.CurrentValue = -5F;
            this.panel2.CurrentValueColor = System.Drawing.Color.Black;
            this.panel2.EnableIndicator = true;
            this.panel2.HandlesBorderColor = System.Drawing.Color.White;
            this.panel2.HandlesHeight = 8;
            this.panel2.IndicatorBorderColor = System.Drawing.Color.Black;
            this.panel2.IndicatorColor = System.Drawing.Color.GreenYellow;
            this.panel2.IndicatorSize = new System.Drawing.Size(20, 20);
            this.panel2.IndicatorText = "";
            this.panel2.IsSimpleIndicator = true;
            this.panel2.LinesColor = System.Drawing.Color.LightGray;
            this.panel2.Location = new System.Drawing.Point(300, 20);
            this.panel2.MiddleHandleColor = System.Drawing.Color.GreenYellow;
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(120, 460);
            this.panel2.StepValue = 10F;
            this.panel2.TabIndex = 4;
            this.panel2.TopValue = 100F;
            this.panel2.TopZone = true;
            this.panel2.TopZoneColor = System.Drawing.Color.DeepSkyBlue;
            this.panel2.TopZoneValue = 50F;
            this.panel2.TwoSliderMode = false;
            // 
            // panel
            // 
            this.panel.AdditionalText = " C";
            this.panel.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
            this.panel.BackColor = System.Drawing.Color.Transparent;
            this.panel.BackgroundWidth = 20;
            this.panel.BorderColor = System.Drawing.Color.Black;
            this.panel.BottomValue = -100F;
            this.panel.BottomZone = true;
            this.panel.BottomZoneColor = System.Drawing.Color.Red;
            this.panel.BottomZoneValue = -50F;
            this.panel.CurrentValue = -5F;
            this.panel.CurrentValueColor = System.Drawing.Color.Black;
            this.panel.EnableIndicator = true;
            this.panel.HandlesBorderColor = System.Drawing.Color.White;
            this.panel.HandlesHeight = 8;
            this.panel.IndicatorBorderColor = System.Drawing.Color.Black;
            this.panel.IndicatorColor = System.Drawing.Color.GreenYellow;
            this.panel.IndicatorSize = new System.Drawing.Size(200, 30);
            this.panel.IndicatorText = "Temp";
            this.panel.IsSimpleIndicator = false;
            this.panel.LinesColor = System.Drawing.Color.LightGray;
            this.panel.Location = new System.Drawing.Point(0, 20);
            this.panel.MiddleHandleColor = System.Drawing.Color.GreenYellow;
            this.panel.Name = "panel";
            this.panel.Size = new System.Drawing.Size(300, 460);
            this.panel.StepValue = 10F;
            this.panel.TabIndex = 2;
            this.panel.TopValue = 100F;
            this.panel.TopZone = true;
            this.panel.TopZoneColor = System.Drawing.Color.DeepSkyBlue;
            this.panel.TopZoneValue = 50F;
            this.panel.TwoSliderMode = false;
            // 
            // SetPointsControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Transparent;
            this.Controls.Add(this.bottomValueLabel);
            this.Controls.Add(this.topValueLabel);
            this.Controls.Add(this.panel1TwoSliderModeCheckBox);
            this.Controls.Add(this.panel2);
            this.Controls.Add(this.panel);
            this.Name = "SetPointsControl";
            this.Size = new System.Drawing.Size(1000, 500);
            this.ResumeLayout(false);

        }

        #endregion
        private SliderControl panel;
        private SliderControl panel2;
        private System.Windows.Forms.CheckBox panel1TwoSliderModeCheckBox;
        private System.Windows.Forms.Label topValueLabel;
        private System.Windows.Forms.Label bottomValueLabel;
    }
}
