/*
 * Copyright 2018 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "include/utils/SkTextUtils.h"

#include "include/core/SkCanvas.h"
#include "include/core/SkFont.h"
#include "include/core/SkFontTypes.h"
#include "include/core/SkMatrix.h"
#include "include/core/SkPath.h"
#include "include/core/SkPoint.h"
#include "include/core/SkScalar.h"
#include "include/core/SkTextBlob.h"
#include "include/private/SkTemplates.h"
#include "src/core/SkFontPriv.h"
#include "include/core/SkTextBlob.h" // P5Skia
#include "src/core/SkTextBlobPriv.h" // P5Skia
#include "include/core/SkFontMetrics.h"  // P5Skia
#include "modules/skshaper/include/SkShaper.h"  // P5Skia


class SkPaint;

void SkTextUtils::Draw(SkCanvas* canvas, const void* text, size_t size, SkTextEncoding encoding,
                       SkScalar x, SkScalar y, const SkFont& font, const SkPaint& paint,
                       Align align) {
    if (align != kLeft_Align) {
        SkScalar width = font.measureText(text, size, encoding);
        if (align == kCenter_Align) {
            width *= 0.5f;
        }
        x -= width;
    }

    canvas->drawTextBlob(SkTextBlob::MakeFromText(text, size, font, encoding), x, y, paint);
}

void SkTextUtils::GetPath(const void* text, size_t length, SkTextEncoding encoding,
                          SkScalar x, SkScalar y, const SkFont& font, SkPath* path) {
// P5Skia
    SkFontMetrics metrics;
    font.getMetrics(&metrics);

    std::unique_ptr<SkShaper> shaper = SkShaper::Make();
    //const int count = font.countText(text, length, SkTextEncoding::kUTF8);

    SkTextBlobBuilderRunHandler builder((const char*)text, {x, y + metrics.fAscent});
    shaper->shape((const char*)text, length, font, true, 10000000, &builder);

    path->reset();

    sk_sp<SkTextBlob> blobShape = builder.makeBlob();

    for (SkTextBlobRunIterator it(blobShape.get()); !it.done(); it.next()) {
        size_t runSize = it.glyphCount();
        if (runSize == 0) {
            continue;
        }

        struct Rec {
            SkPath* fDst;
            const SkPoint* fPos;
        } rec = {path, it.points()};

        font.getPaths(
                it.glyphs(),
                runSize,
                [](const SkPath* src, const SkMatrix& mx, void* ctx) {
                    Rec* rec = (Rec*)ctx;
                    if (src) {
                        SkMatrix m(mx);
                        m.postTranslate(rec->fPos->fX, rec->fPos->fY);
                        rec->fDst->addPath(*src, m);
                    }
                    rec->fPos += 1;
                },
                &rec);

    }
//
    /*
    SkAutoToGlyphs ag(font, text, length, encoding);
    SkAutoTArray<SkPoint> pos(ag.count());
    font.getPos(ag.glyphs(), ag.count(), pos.get(), {x, y});

    struct Rec {
        SkPath* fDst;
        const SkPoint* fPos;
    } rec = { path, pos.get() };

    path->reset();
    font.getPaths(ag.glyphs(), ag.count(), [](const SkPath* src, const SkMatrix& mx, void* ctx) {
        Rec* rec = (Rec*)ctx;
        if (src) {
            SkMatrix m(mx);
            m.postTranslate(rec->fPos->fX, rec->fPos->fY);
            rec->fDst->addPath(*src, m);
        }
        rec->fPos += 1;
    }, &rec);
    */
}

