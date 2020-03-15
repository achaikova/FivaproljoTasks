#include "Block.h"

Block::Block(QPoint position, const QString &file_name) {
    setPixmap(QPixmap(file_name).scaled(block_width, block_height));
    setPos(position);
}

int Block::type() const {
    return Type;
}

QRectF Block::boundingRect() const {
    return QRectF(0, 0, 50, 50);
}

void Block::add_color(int color) {
    switch (color) {
        case 1:
            setPixmap(QPixmap(QPixmap("../images/green_block.jpg")).scaled(block_width, block_height));
            break;
        default:
            break;
    }
}

void Block::change_color(int color) {
    if (color_ == color) {
	return;
    }
    color_ = color;
    delete recolor_timer_;
    next_texture_ = std::queue<std::string>(); // clear queue, mb race
    recolor_timer_ = new QTimer(this);
    QObject::connect(recolor_timer_, SIGNAL(timeout()), this, SLOT(change_color_()));
    next_texture_.push("../images/orange_block.jpg");
    next_texture_.push("../images/green_block.jpg");
    recolor_timer_->start();
    recolor_timer_->setInterval(100);
}

void Block::change_color_() {
    if (next_texture_.empty()) {
	delete recolor_timer_;
	recolor_timer_ = nullptr;
    } else {
	setPixmap(QPixmap(QPixmap(next_texture_.front().c_str())).scaled(block_width, block_height));
	next_texture_.pop();
    }
}
	
    
