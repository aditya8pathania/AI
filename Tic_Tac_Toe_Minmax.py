class TicTacToe:
    def __init__(self):
        self.board = [2] * 9  # 2 means square is blank
        self.turn = 1  # Move counter

    def print_board(self):
        symbols = {2: ' ', 3: 'X', 5: 'O'}
        for i in range(3):
            row = []
            for j in range(3):
                pos = i * 3 + j
                if self.board[pos] == 2:
                    row.append(str(pos + 1))  # Show number if square is blank
                else:
                    row.append(symbols[self.board[pos]])
            print(" | ".join(row))
            print("-" * 9)

    def check_win(self):
        for i in range(3):
            if self.board[i * 3] == self.board[i * 3 + 1] == self.board[i * 3 + 2] != 2:
                return True
            if self.board[i] == self.board[i + 3] == self.board[i + 6] != 2:
                return True

        if self.board[0] == self.board[4] == self.board[8] != 2 or self.board[2] == self.board[4] == self.board[6] != 2:
            return True

        return False

    def minimax(self, depth, is_maximizing, max_depth):
        if depth == max_depth or self.check_win():
            if self.check_win():
                return -10 if is_maximizing else 10
            if all(square != 2 for square in self.board):  # Draw
                return 0

        if is_maximizing:  # O's turn
            best_score = float('-inf')
            for i in range(9):
                if self.board[i] == 2:
                    self.board[i] = 5  # O
                    score = self.minimax(depth + 1, False, max_depth)
                    self.board[i] = 2  # Undo move
                    best_score = max(score, best_score)
            return best_score
        else:  # X's turn
            best_score = float('inf')
            for i in range(9):
                if self.board[i] == 2:
                    self.board[i] = 3  # X
                    score = self.minimax(depth + 1, True, max_depth)
                    self.board[i] = 2  # Undo move
                    best_score = min(score, best_score)
            return best_score

    def check_immediate_win_or_block(self, player):
        for i in range(9):
            if self.board[i] == 2:  # If the spot is available
                self.board[i] = player
                if self.check_win():
                    self.board[i] = 2  # Undo the move
                    return i  # Return the winning/blocking position
                self.board[i] = 2  # Undo the move
        return -1  # No immediate win or block

    def find_best_move(self, max_depth):
        # First, check if AI can win in the next move
        win_move = self.check_immediate_win_or_block(5)
        if win_move != -1:
            return win_move

        # Then, check if the player can win in the next move and block it
        block_move = self.check_immediate_win_or_block(3)
        if block_move != -1:
            return block_move

        # Otherwise, use minimax to find the best move
        best_score = float('-inf')
        best_move = -1
        for i in range(9):
            if self.board[i] == 2:
                self.board[i] = 5  # O
                score = self.minimax(0, False, max_depth)
                self.board[i] = 2  # Undo move
                if score > best_score:
                    best_score = score
                    best_move = i
        return best_move

    def user_input(self):
        while True:
            self.print_board()  # Show the board before asking for input
            try:
                move = int(input("Player X, enter your move (1-9): "))
                if move < 1 or move > 9 or self.board[move - 1] != 2:
                    print("Invalid move, try again.")
                else:
                    return move
            except ValueError:
                print("Please enter a valid number between 1 and 9.")

    def play(self, max_depth):
        while True:
            if self.turn > 9:
                print("It's a draw!")
                break

            if self.turn % 2 == 1:  # Player X's turn
                move = self.user_input()
                self.board[move - 1] = 3  # Player X
            else:  # Player O's turn (AI)
                move = self.find_best_move(max_depth)
                self.board[move] = 5  # Player O

            self.turn += 1

            if self.check_win():
                self.print_board()
                print(f"Player {'X' if self.turn % 2 == 1 else 'O'} wins!")
                break


if __name__ == "__main__":
    game = TicTacToe()
   
    # Prompt the user for the max depth (1 to 4)
    while True:
        try:
            max_depth = int(input("Enter minimax depth (1 to 4): "))
            if max_depth < 1 or max_depth > 4:
                print("Invalid depth, try again.")
            else:
                break
        except ValueError:
            print("Please enter a valid number between 1 and 4.")
   
    game.play(max_depth)
