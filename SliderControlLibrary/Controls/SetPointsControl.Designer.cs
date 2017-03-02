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
            this.panel = new T3000Controls.SliderControl();
            this.SuspendLayout();
            // 
            // panel2
            // 
            this.panel2.AdditionalText = " F";
            this.panel2.BackColor = System.Drawing.Color.Transparent;
            this.panel2.BackgroundWidth = 49;
            this.panel2.BorderColor = System.Drawing.Color.Black;
            this.panel2.BottomValue = 0F;
            this.panel2.BottomZone = true;
            this.panel2.BottomZoneColor = System.Drawing.Color.Red;
            this.panel2.BottomZoneValue = 33F;
            this.panel2.CurrentValue = 40F;
            this.panel2.CurrentValueColor = System.Drawing.Color.Black;
            this.panel2.EnableIndicator = true;
            this.panel2.HandlesBorderColor = System.Drawing.Color.White;
            this.panel2.HandlesHeight = 8;
            this.panel2.IndicatorBorderColor = System.Drawing.Color.Black;
            this.panel2.IndicatorColor = System.Drawing.Color.GreenYellow;
            this.panel2.IndicatorSize = new System.Drawing.Size(23, 19);
            this.panel2.IndicatorText = "";
            this.panel2.IsSimpleIndicator = true;
            this.panel2.LinesColor = System.Drawing.Color.LightGray;
            this.panel2.Location = new System.Drawing.Point(316, 39);
            this.panel2.MiddleHandleColor = System.Drawing.Color.GreenYellow;
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(179, 263);
            this.panel2.StepValue = 10F;
            this.panel2.TabIndex = 4;
            this.panel2.TopValue = 100F;
            this.panel2.TopZone = true;
            this.panel2.TopZoneColor = System.Drawing.Color.DeepSkyBlue;
            this.panel2.TopZoneValue = 66F;
            this.panel2.TwoHandleControl = false;
            // 
            // panel
            // 
            this.panel.AdditionalText = " C";
            this.panel.BackColor = System.Drawing.Color.Transparent;
            this.panel.BackgroundWidth = 20;
            this.panel.BorderColor = System.Drawing.Color.Black;
            this.panel.BottomValue = -5555F;
            this.panel.BottomZone = true;
            this.panel.BottomZoneColor = System.Drawing.Color.Red;
            this.panel.BottomZoneValue = -2222F;
            this.panel.CurrentValue = 188F;
            this.panel.CurrentValueColor = System.Drawing.Color.Black;
            this.panel.EnableIndicator = true;
            this.panel.HandlesBorderColor = System.Drawing.Color.White;
            this.panel.HandlesHeight = 8;
            this.panel.IndicatorBorderColor = System.Drawing.Color.Black;
            this.panel.IndicatorColor = System.Drawing.Color.GreenYellow;
            this.panel.IndicatorSize = new System.Drawing.Size(168, 50);
            this.panel.IndicatorText = "Temp";
            this.panel.IsSimpleIndicator = false;
            this.panel.LinesColor = System.Drawing.Color.LightGray;
            this.panel.Location = new System.Drawing.Point(15, 19);
            this.panel.MiddleHandleColor = System.Drawing.Color.Yellow;
            this.panel.Name = "panel";
            this.panel.Size = new System.Drawing.Size(278, 310);
            this.panel.StepValue = 1000F;
            this.panel.TabIndex = 2;
            this.panel.TopValue = 8300F;
            this.panel.TopZone = true;
            this.panel.TopZoneColor = System.Drawing.Color.DeepSkyBlue;
            this.panel.TopZoneValue = 6000F;
            this.panel.TwoHandleControl = false;
            // 
            // SetPointsControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Transparent;
            this.Controls.Add(this.panel2);
            this.Controls.Add(this.panel);
            this.Name = "SetPointsControl";
            this.Size = new System.Drawing.Size(498, 359);
            this.ResumeLayout(false);

        }

        #endregion
        private SliderControl panel;
        private SliderControl panel2;
    }
}
