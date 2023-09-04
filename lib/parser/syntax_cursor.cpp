#include "tscpp/parser/syntax_cursor.h"

using namespace tscpp;

Node SyntaxCursor::currentNode(int position) {
    lastQueriedPosition = position;

    return *current;
}

void SyntaxCursor::findHighestListElementThatStartsAtPosition(int position) {
}
