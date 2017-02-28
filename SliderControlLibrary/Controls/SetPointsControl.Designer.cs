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
            this.panel2 = new T3000Controls.SliderControl();
            this.smallIndicator = new T3000Controls.SmallIndicatorControl();
            this.panel = new T3000Controls.SliderControl();
            this.indicator = new T3000Controls.IndicatorControl();
            this.SuspendLayout();
            // 
            // panel2
            // 
            this.panel2.BackColor = System.Drawing.Color.Transparent;
            this.panel2.BackgroundWidth = 49;
            this.panel2.BorderColor = System.Drawing.Color.Black;
            this.panel2.BottomValue = 0F;
            this.panel2.BottomZone = true;
            this.panel2.BottomZoneColor = System.Drawing.Color.Red;
            this.panel2.BottomZoneValue = 33F;
            this.panel2.CurrentValue = 50F;
            this.panel2.CurrentValueColor = System.Drawing.Color.Black;
            this.panel2.HandlesAdditionalText = " F";
            this.panel2.HandlesHeight = 8;
            this.panel2.LinesColorColor = System.Drawing.Color.LightGray;
            this.panel2.Location = new System.Drawing.Point(350, 37);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(116, 279);
            this.panel2.StepValue = 10F;
            this.panel2.TabIndex = 4;
            this.panel2.TopValue = 100F;
            this.panel2.TopZone = true;
            this.panel2.TopZoneColor = System.Drawing.Color.DeepSkyBlue;
            this.panel2.TopZoneValue = 66F;
            this.panel2.TwoHandleControl = false;
            // 
            // smallIndicator
            // 
            this.smallIndicator.BackColor = System.Drawing.Color.GreenYellow;
            this.smallIndicator.BorderColor = System.Drawing.Color.Black;
            this.smallIndicator.Location = new System.Drawing.Point(330, 167);
            this.smallIndicator.Name = "smallIndicator";
            this.smallIndicator.Size = new System.Drawing.Size(19, 17);
            this.smallIndicator.TabIndex = 3;
            this.smallIndicator.Value = 0F;
            // 
            // panel
            // 
            this.panel.BackColor = System.Drawing.Color.Transparent;
            this.panel.BackgroundWidth = 20;
            this.panel.BorderColor = System.Drawing.Color.Black;
            this.panel.BottomValue = -5555F;
            this.panel.BottomZone = true;
            this.panel.BottomZoneColor = System.Drawing.Color.Red;
            this.panel.BottomZoneValue = -2222F;
            this.panel.CurrentValue = 52F;
            this.panel.CurrentValueColor = System.Drawing.Color.Black;
            this.panel.HandlesAdditionalText = " C";
            this.panel.HandlesHeight = 8;
            this.panel.LinesColorColor = System.Drawing.Color.LightGray;
            this.panel.Location = new System.Drawing.Point(170, 37);
            this.panel.Name = "panel";
            this.panel.Size = new System.Drawing.Size(127, 279);
            this.panel.StepValue = 1000F;
            this.panel.TabIndex = 2;
            this.panel.TopValue = 8300F;
            this.panel.TopZone = true;
            this.panel.TopZoneColor = System.Drawing.Color.DeepSkyBlue;
            this.panel.TopZoneValue = 6000F;
            this.panel.TwoHandleControl = true;
            // 
            // indicator
            // 
            this.indicator.BackColor = System.Drawing.Color.GreenYellow;
            this.indicator.BorderColor = System.Drawing.Color.Black;
            this.indicator.IndicatorText = "Temp";
            this.indicator.Location = new System.Drawing.Point(3, 149);
            this.indicator.Name = "indicator";
            this.indicator.Size = new System.Drawing.Size(168, 55);
            this.indicator.TabIndex = 1;
            this.indicator.Value = 50F;
            // 
            // SetPointsControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Transparent;
            this.Controls.Add(this.panel2);
            this.Controls.Add(this.smallIndicator);
            this.Controls.Add(this.panel);
            this.Controls.Add(this.indicator);
            this.Name = "SetPointsControl";
            this.Size = new System.Drawing.Size(498, 359);
            this.ResumeLayout(false);

        }

        #endregion

        private T3000Controls.IndicatorControl indicator;
        private SliderControl panel;
        private SmallIndicatorControl smallIndicator;
        private SliderControl panel2;
    }
}
