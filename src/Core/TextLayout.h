#pragma once

#include <Core/Vector.h>
#include <Core/Utils.h>

#include <Core/Draw.h>

#include <Core/FontData.h>

namespace Vortex {

// Tells how many trailing bytes follow a given UTF-8 leading byte.
extern const uchar utf8TrailingBytes[256];

// Used in UTF-8 multibyte decoding to cancel out the non-charcode bits.
extern const uint utf8MultibyteResidu[6];

// Character glyph in a text layout.
struct LGlyph
{
	const Glyph* glyph;
	int x, charIndex;
};

// Markup tag in a text layout.
struct LMarkup
{
	struct SetFloat { float value; };

	enum Type
	{
		SET_TEXT_COLOR,
		SET_SHADOW_COLOR,
	};

	int glyphIndex;
	Type type;

	union
	{
		color32 setTextColor;
		color32 setShadowColor;
	};
};

// Line data in a text layout.
struct LLine
{
	int beginGlyph, endGlyph;
	int x, y, w, top, bottom;
};

// Coloured quad in a text layout.
struct LQuad
{
	int line, x, w;
	color32 color;
};

// Contains the entire text layout.
struct LLayout
{
	struct QuadData { bool enabled; int x; color32 color; };

	const Glyph* previousGlyph;

	FontData* baseFont, *font;
	int baseFontSize, fontSize;
	color32 baseTextColor, textColor;
	color32 baseShadowColor, shadowColor;

	uint flags;
	Text::Align align;
	bool useKerning;

	int textW, textH;
	int maxLineW;   // Maximum line width.
	int lineTop;    // Vertical offset from baseline to line top.
	int lineBottom; // Vertical offset from baseline to line bottom.
	int lineBeginGlyph, lineW;
	int lineIndex;
	int charIndex, nextCharIndex;

	TextStyle style, defaultStyle;
	QuadData fgQuad;
	QuadData bgQuad;

	Vector<LQuad> fgQuads;
	Vector<LQuad> bgQuads;
	Vector<LGlyph> glyphs;
	Vector<LMarkup> markup;
	Vector<LLine> lines;

	int stringLength;
};

struct TextLayout {

static void create();
static void destroy();
static void endFrame();

static LLayout& get();

static vec2i getTextPos(recti rect);
static recti getTextBB(vec2i pos);

}; // TextArranger.

}; // namespace Vortex
