using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Ribbon;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using Xceed.Wpf.Toolkit.PropertyGrid.Attributes;

namespace HrMeshConvert
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : RibbonWindow
    {

        private Hr.HrMeshConvertWrapper core_;

        public MainWindow()
        {
            InitializeComponent();
        }

        private void MainWindowLoaded(object sender, RoutedEventArgs e)
        {
            IntPtr wnd = editor_wnd.Handle;
            core_ = new Hr.HrMeshConvertWrapper(wnd);
            
        }

        private void MainWindowUnloaded(object sender, RoutedEventArgs e)
        {
            core_.Dispose();
            core_ = null;
        }


        protected override void OnRender(DrawingContext drawingContext)
        {
            base.OnRender(drawingContext);


        }

        private void OpenClick(object sender, RoutedEventArgs e)
        {

        }

        private void SaveClick(object sender, RoutedEventArgs e)
        {

        }

        private void SaveAsClick(object sender, RoutedEventArgs e)
        {

        }

        private void AssignMaterialClick(object sender, RoutedEventArgs e)
        {

        }

        private void CopyMaterialClick(object sender, RoutedEventArgs e)
        {

        }

        private void DeleteMaterialClick(object sender, RoutedEventArgs e)
        {

        }

        private void ImportMaterialClick(object sender, RoutedEventArgs e)
        {

        }

        private void ExportMaterialClick(object sender, RoutedEventArgs e)
        {

        }

        private void UndoClick(object sender, RoutedEventArgs e)
        {

        }

        private void RedoClick(object sender, RoutedEventArgs e)
        {

        }

        private void VisualizeSelectionChanged(object sender, RoutedPropertyChangedEventArgs<object> e)
        {

        }

        private void EditorWindowSizeChanged(object sender, SizeChangedEventArgs e)
        {

        }

        private void EditorBGDragEnter(object sender, DragEventArgs e)
        {

        }

        private void EditorBGDrop(object sender, DragEventArgs e)
        {

        }

        private void EditorMouseMove(object sender, System.Windows.Forms.MouseEventArgs e)
        {

        }

        private void EditorMouseDown(object sender, System.Windows.Forms.MouseEventArgs e)
        {

        }

        private void EditorMouseUp(object sender, System.Windows.Forms.MouseEventArgs e)
        {

        }

        private void EditorKeyPress(object sender, System.Windows.Forms.KeyPressEventArgs e)
        {

        }

        private void PropertyGridValueChanged(object sender, Xceed.Wpf.Toolkit.PropertyGrid.PropertyValueChangedEventArgs e)
        {

        }


    }
}
