# University of Washington, Programming Languages, Homework 6, hw6runner.rb

# This is the only file you turn in, so do not modify the other files as
# part of your solution.
#require ./hw6provided.rb

class MyPiece < Piece
  # The constant All_My_Pieces should be declared here
  All_My_Pieces = [[[[0, 0], [1, 0], [0, 1], [1, 1]]],  # square (only needs one)
                  rotations([[0, 0], [-1, 0], [1, 0], [0, -1]]), # T
                  [[[0, 0], [-1, 0], [1, 0], [2, 0]], # long (four cells, only needs two)
                  [[0, 0], [0, -1], [0, 1], [0, 2]]],
                  rotations([[0, 0], [0, -1], [0, 1], [1, 1]]), # L
                  rotations([[0, 0], [0, -1], [0, 1], [-1, 1]]), # inverted L
                  rotations([[0, 0], [-1, 0], [0, -1], [1, -1]]), # S
                  rotations([[0, 0], [1, 0], [0, -1], [-1, -1]]), # Z
                  rotations([[0,0], [-1,0], [-1,1], [0,1],[1,1]]),
                  [[[0,0],[0,-2],[0,-1],[0,1], [0,2]], # long (five cells)
                  [[0,0], [-2,0], [-1,0], [1,0], [2,0]]],
                  rotations([[0,0], [0,-1], [1,0]])]   


# your enhancements here
  def self.next_piece (board)
    MyPiece.new(All_My_Pieces.sample, board)
  end

  def board
    @board
  end

  def all_rotations
    @all_rotations
  end

end

class MyBoard < Board
# your enhancements here
  def initialize (game)
    @grid = Array.new(num_rows) {Array.new(num_columns)}
    @current_block = MyPiece.next_piece(self)
    @score = 0
    @game = game
    @delay = 500
    #@one_piece= false
    @next_block = nil
  end

  def one_piece
    @one_piece
  end

  def next_block
    @next_block
  end

  def next_piece
#    if one_piece
#        @current_block = Mypiece.new([[[0,0]]], self.board)
#    else
#        @current_block = MyPiece.next_piece(self)
#        one_piece = false
#    end
    if @next_block != nil
        @current_block = @next_block
        @next_block = MyPiece.next_piece(self)
    else
        @current_block = MyPiece.next_piece(self)
    end
    @current_pos = nil
  end

  def store_current
    locations = @current_block.current_rotation
    displacement = @current_block.position
    (0..locations.size()-1).each{|index| 
      current = locations[index];
      @grid[current[1]+displacement[1]][current[0]+displacement[0]] = 
      @current_pos[index]
    }
    remove_filled
    @delay = [@delay - 2, 80].max
  end

  def rotate_180_degree
    if !game_over? and @game.is_running?
      @current_block.move(0, 0, 1)
      @current_block.move(0, 0, 1)
    end
    draw
  end

  def cheat
    one_piece = [[[0,0]]]
    if score >= 100 and one_piece != @current_block.all_rotations
        #one_piece = true
        @next_block = MyPiece.new([[[0,0]]], @current_block.board)
        set_score(score-100)
    end
  end

  def set_score(new_score)
      @score = new_score
  end
end

class MyTetris < Tetris
# your enhancements here
  def set_board
    @canvas = TetrisCanvas.new
    @board = MyBoard.new(self)
    @canvas.place(@board.block_size * @board.num_rows + 3,
                  @board.block_size * @board.num_columns + 6, 24, 80)
    @board.draw
  end

  #def initialize
  #    super
  #end
  def key_bindings  
    super
    @root.bind('u', proc {@board.rotate_180_degree}) 
    @root.bind('c', proc {@board.cheat})
  end
end
