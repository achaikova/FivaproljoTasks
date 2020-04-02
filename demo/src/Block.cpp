#include "Block.h"



Block::Block(QPoint position, const QString &file_name)
    : next_texture_(){

    setPixmap(QPixmap(file_name).scaled(block_width, block_height));
    setPos(position);
}

QRectF Block::boundingRect() const {
    return QRectF(0, 0, block_width, block_height);
}

void Block::add_color(Utilities::Color color) {
    switch (color) {
        case Utilities::Color::GREEN:
            setPixmap(QPixmap(QPixmap("images/green_block.jpg")).scaled(block_width, block_height));
            break;
        // other colors are not yet implemented
        default:
            break;
    }
}

void Block::change_color(Utilities::Color color) {
    if (color_ == color) {
	    return;
    }

    ///TODO Сделать нормальную анимацию вместо этого
    color_ = color;
    delete recolor_timer_;
    recolor_timer_ = new QTimer(this);
    QObject::connect(recolor_timer_, SIGNAL(timeout()), this, SLOT(change_color_helper_()));
    switch (color) {
	case Utilities::Color::GREEN:
	    next_texture_.push("images/orange_block.jpg");
	    next_texture_.push("images/green_block.jpg");
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
