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
            this.panel = new T3000Controls.SliderControl();
            this.indicator = new T3000Controls.IndicatorControl();
            this.SuspendLayout();
            // 
            // panel
            // 
            this.panel.BackColor = System.Drawing.Color.Transparent;
            this.panel.BottomValue = 0F;
            this.panel.BottomZone = true;
            this.panel.BottomZoneValue = 33F;
            this.panel.CurrentValue = 50F;
            this.panel.Location = new System.Drawing.Point(170, 37);
            this.panel.Name = "panel";
            this.panel.Size = new System.Drawing.Size(202, 279);
            this.panel.StepValue = 10F;
            this.panel.TabIndex = 2;
            this.panel.TopValue = 100F;
            this.panel.TopZone = true;
            this.panel.TopZoneValue = 66F;
            this.panel.TwoHandleControl = false;
            // 
            // indicator
            // 
            this.indicator.BackColor = System.Drawing.Color.GreenYellow;
            this.indicator.BorderColor = System.Drawing.Color.Black;
            this.indicator.IndicatorText = "Temp";
            this.indicator.Location = new System.Drawing.Point(3, 149);
            this.indicator.Name = "indicator";
            this.indicator.Size = new System.Drawing.Size(169, 55);
            this.indicator.TabIndex = 1;
            this.indicator.Value = 50F;
            // 
            // SetPointsControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Transparent;
            this.Controls.Add(this.panel);
            this.Controls.Add(this.indicator);
            this.Name = "SetPointsControl";
            this.Size = new System.Drawing.Size(412, 359);
            this.ResumeLayout(false);

        }

        #endregion

        private T3000Controls.IndicatorControl indicator;
        private SliderControl panel;
    }
}
