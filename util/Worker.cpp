//
// Created by thanhphu on 19. 11. 7..
//

#include "Worker.h"

void Worker::run() {
    while (!shouldStop.load()) {
        int index = r->randKeys();
        auto expectedValue = long_string + std::to_string(index);
        if (r->rand100() < opts.readWeight) {
            readCount++;
            // Do read
            db->get(std::to_string(index), readResult);
            // Verify result
//            if (*readResult != expectedValue) {
//                std::cout << "Read error at index=" << index << std::endl;
//            }
        } else {
            writeCount++;
            // Do write
            db->put(std::to_string(index), expectedValue);
        }
    }
}

Worker::Worker(struct options &_opts, avis::StateDB *_db, RandomEngine* _r, int _id) {
    shouldStop.store(false);
    opts = _opts;
    db = _db;
    r = _r;
    id = _id;
    readCount = 0;
    writeCount = 0;
    readResult = new std::string;
    long_string = std::string(opts.stringLength,  'x');
}

unsigned long Worker::getReadCount() {
    return readCount;
}

unsigned long Worker::getWriteCount() {
    return writeCount;
}

void Worker::stop() {
    shouldStop.store(true);
}

Worker::~Worker() {
    // delete readResult;
}
