#include <QApplication>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QFileDialog>
#include <QColorDialog>
#include <QFontDialog>

class MainWindow : public QWidget {
public:
    MainWindow() {
        QTabWidget *tabWidget = new QTabWidget(this);

        // Create Captain Tab
        captainLabel = new QLabel("隊長姓名:林承志\n學號: 41243218\n隊員姓名: 黃培峰\n學號: 41243145\n隊員姓名: 黃境安\n學號: 41243146\n隊員姓名: 陳有臨\n學號: 50915133\n");
        tabWidget->addTab(createCaptainTab(), "隊長頁");

        // Create Member Tabs with specific features enabled
        tabWidget->addTab(createMemberTab("隊員 1", true, false, false), "隊員 1");
        tabWidget->addTab(createMemberTab("隊員 2", false, true, false), "隊員 2");
        tabWidget->addTab(createMemberTab("隊員 3", false, false, true), "隊員 3");

        QVBoxLayout *mainLayout = new QVBoxLayout;
        mainLayout->addWidget(tabWidget);
        setLayout(mainLayout);
    }

private:
    QLabel *captainLabel; // Store captain label for access in member tabs

    // Function to create the Captain tab
    QWidget* createCaptainTab() {
        QWidget *tab = new QWidget();
        QVBoxLayout *layout = new QVBoxLayout;
        layout->addWidget(captainLabel);
        tab->setLayout(layout);
        return tab;
    }

    // Function to create a Member tab with specified buttons
    QWidget* createMemberTab(const QString& labelText, bool colorButton, bool styleButton, bool fileButton) {
        QWidget *tab = new QWidget();
        QVBoxLayout *layout = new QVBoxLayout;

        if (colorButton) {
            QPushButton *colorChangeButton = new QPushButton("改變隊長文字顏色");
            connect(colorChangeButton, &QPushButton::clicked, [=]() {
                QColor color = QColorDialog::getColor(Qt::black, this);
                if (color.isValid()) {
                    captainLabel->setStyleSheet(QString("color: %1;").arg(color.name()));
                }
            });
            layout->addWidget(colorChangeButton);
        }

        if (styleButton) {
            QPushButton *fontChangeButton = new QPushButton("改變隊長文字樣式");
            connect(fontChangeButton, &QPushButton::clicked, [=]() {
                bool ok;
                QFont font = QFontDialog::getFont(&ok, QFont(), this);
                if (ok) {
                    captainLabel->setFont(font); // Change the font of the captain label
                }
            });
            layout->addWidget(fontChangeButton);
        }

        if (fileButton) {
            QPushButton *fileSelectButton = new QPushButton("選擇檔案");
            QLabel *member3Label = new QLabel("選擇的文件: 無"); // Create label for member 3
            layout->addWidget(member3Label); // Add to the layout for member 3 tab

            connect(fileSelectButton, &QPushButton::clicked, [=]() {
                QString filePath = QFileDialog::getOpenFileName(this, "選擇檔案");
                if (!filePath.isEmpty()) {
                    member3Label->setText("選擇的文件: " + filePath); // Show selected file in member 3 label
                }
            });
            layout->addWidget(fileSelectButton);
        }

        tab->setLayout(layout);
        return tab;
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow window;
    window.resize(400, 300);  // Set initial window size
    window.show();
    return app.exec();
}
