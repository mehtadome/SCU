# roomba has an indexer to maintain position, actionPoints to mark tasks done
class MyAgent:
    
    # pass state array to determine values of cd1, cd2, lr
    def __init__(self, indexer, actionPoints=0, sequence=[]): 

        # indexer is a random index of 2-element array
        self.indexer = indexer
        self.actionPoints = actionPoints
        self.sequence = sequence

       
    # suck function to move to left square
    def suck(self, state):
        # check if already clean before sucking
        if (state[self.indexer] != "clean"):
            # change state's element to "clean"
            state[self.indexer] = "clean"
            # increment action points
            self.actionPoints += 1 
            # add to sequence notes
            self.sequence.append("Sucked")
    
    # left function to move to left square
    def goLeft(self):
        # set new position to left
        self.indexer = 0
        # incremenet action points
        self.actionPoints += 1
        # add to sequence notes
        self.sequence.append("Went Left")
    
    # right function to move to right square
    def goRight(self):
        # set new position to left
        self.indexer = 1
        # incremenet action points
        self.actionPoints += 1
        # add to sequence notes
        self.sequence.append("Went Right")

    def getState(self, state):
        print ("========================================")

        print ("Current State:")
        print ("The left square is:", state[0], end=". ")
        print ("The right square is:", state[1], end=". ")
        print ("The agent is at:", self.indexer, end=".\n")

        print ("========================================")
        print ("****************************************\n")

# function for determining which action to take 
    # based upon data structure input

# takes object of class and the state <array>
def whichOne(myRoomba, state):
    # get state details
    myRoomba.getState(state)

    # if agent is on the left, go right
    if (myRoomba.indexer == 0):
        # clean if necessary
        myRoomba.suck(state)
        # go right
        myRoomba.goRight()
        
    # if agent is on the right, go left
    else:
        # clean if necessary
        myRoomba.suck(state)
        # go left
        myRoomba.goLeft()


    
    


