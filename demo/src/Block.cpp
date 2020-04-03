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

void Block::change_color(Utilities::Color color) {
    if (color_ == color) {
        return;
    }
    color_ = color;
    if (recolor_timer_) {
        delete recolor_timer_;
    }
    next_texture_ = std::queue<std::string>(); // clear queue, mb race
    recolor_timer_ = new QTimer(this);
    QObject::connect(recolor_timer_, SIGNAL(timeout()), this, SLOT(change_color_helper_()));
    switch (color) {
        case Utilities::Color::GREEN:
            next_texture_.push("images/white_block.jpg");
            next_texture_.push("images/green_block1.jpg");
            next_texture_.push("images/green_block.jpg");
            break;
        case Utilities::Color::YELLOW:
            next_texture_.push("images/white_block.jpg");
            next_texture_.push("images/orange_block1.jpg");
            next_texture_.push("images/orange_block.jpg");
            break;
        default:
            break;
    }
    recolor_timer_->start();
    recolor_timer_->setInterval(50);
}

void Block::change_color_helper_() {
    if (next_texture_.empty()) {
	delete recolor_timer_;
	recolor_timer_ = nullptr;
    } else {
	setPixmap(QPixmap(QPixmap(next_texture_.front().c_str())).scaled(block_width, block_height));
	next_texture_.pop();
    }
}
