#include "stickerpicker.h"
#include "ui_stickerpicker.h"
StickerPicker::StickerPicker(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::StickerPicker)
{
    ui->setupUi(this);
}
StickerPicker::~StickerPicker()
{
    delete ui;
}
QString StickerPicker::getSelectedSticker() const
{
    return selectedSticker;
}
void StickerPicker::on_btnSun_clicked()
{
    selectedSticker = "sun";
    accept();
}
void StickerPicker::on_btnRainbow_clicked()
{
    selectedSticker = "rainbow";
    accept();
}
void StickerPicker::on_btnMoon_clicked()
{
    selectedSticker = "moon";
    accept();
}
void StickerPicker::on_btnFlower_clicked()
{
    selectedSticker = "flower";
    accept();
}
void StickerPicker::on_btnCoffee_clicked()
{
    selectedSticker = "coffee";
    accept();
}
void StickerPicker::on_btnLeaf_clicked()
{
    selectedSticker = "leaf";
    accept();
}
void StickerPicker::on_btnSparkle_clicked()
{
    selectedSticker = "sparkle";
    accept();
}
void StickerPicker::on_btnButterfly_clicked()
{
    selectedSticker = "butterfly";
    accept();
}