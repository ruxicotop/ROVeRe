using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using ExcelLibrary.Office.Excel;
using System.IO.Ports;

namespace WindowsFormsApplication2
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            serialPort1.BaudRate = 9600;
            serialPort1.PortName = "COM8";
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (!serialPort1.IsOpen) serialPort1.Open();
            label10.Text = "Conectat";
        }

        private void button2_Click(object sender, EventArgs e)
        {
            serialPort1.Close();
            label10.Text = "Deconectat";
        }

        private void button3_Click(object sender, EventArgs e)
        {
            timer1.Start();
            string filename = "Test.xls";
            Workbook workbook = new Workbook();
            Worksheet sheet = new Worksheet("Test");
            workbook.Worksheets.Add(sheet);
            sheet.Cells[0,0] = new Cell("Temperatura");
            sheet.Cells[1,0] = new Cell("Umiditate");
            sheet.Cells[2,0] = new Cell("Presiune");
            sheet.Cells[3,0] = new Cell("Concentratia de CO");
            for (int i = 4; i < 100; i++)
                sheet.Cells[i, 0] = new Cell("");
            int k = 0;
            string celula;
            bool ok=true;
            while (serialPort1.IsOpen)
            {
                k++;
                 celula = serialPort1.ReadTo("!");
                 label11.Text = celula+"*C";
                sheet.Cells[0, k] = new Cell(celula);
                celula = serialPort1.ReadTo("!");
                label12.Text = celula + "%";
                sheet.Cells[1, k] = new Cell(celula);
               celula = serialPort1.ReadTo("!");
                  label13.Text = celula + "Pa";
                  sheet.Cells[2, k] = new Cell(celula);
                  label14.Text = serialPort1.ReadTo("!") + "*C";
                  celula = serialPort1.ReadTo("!");
                  label15.Text = celula + "ppm";
                  sheet.Cells[3, k] = new Cell(celula);
                workbook.Save(filename);
            }
            workbook.Save(filename);
        }

    }
}
