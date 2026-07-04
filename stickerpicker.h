#ifndef STICKERPICKER_H
#define STICKERPICKER_H
#include <QDialog>
namespace Ui {
class StickerPicker;
}
class StickerPicker : public QDialog
{
    Q_OBJECT
public:
    explicit StickerPicker(QWidget *parent = nullptr);
    ~StickerPicker();

    QString getSelectedSticker() const;

private slots:
    void on_btnSun_clicked();
    void on_btnRainbow_clicked();
    void on_btnMoon_clicked();
    void on_btnFlower_clicked();
    void on_btnCoffee_clicked();
    void on_btnLeaf_clicked();
    void on_btnSparkle_clicked();
    void on_btnButterfly_clicked();

private:
    Ui::StickerPicker *ui;
    QString selectedSticker;
};
#endif // STICKERPICKER_H