import roomba
# random number (static implementation)
import random

def isDone(state):
    if (state[0] and state[1] == "clean"):
        return True
    else:
        return False

def main():
    # create the state
    state = ["dirty", "dirty"]  # 1st test case
    # state = ["clean", "dirty"]  # 2nd test case
    # state = ["dirty", "clean"]  # 3rd test case
    # state = ["clean", "clean"] # 4th test case

    # random indexer with value 0 or 1
    myIndexer = random.randint(0,1)
    # print ("The random indexer is", myIndexer, end=".\n\n")

    myRoomba = roomba.MyAgent(myIndexer)

    print ("****************")
    print ("Agent created.")
    print ("****************")
    
    # precondition to loop only until done
    whileLooper = True

    while (whileLooper == True):
        # end if done
        if (isDone(state) == True):
            myRoomba.getState(state)
            whileLooper = False
            
        roomba.whichOne(myRoomba, state)
        
        

    # print sequence list and actions taken
    print ("Sequence history:", myRoomba.sequence)
    print ("Total # of actions:", myRoomba.actionPoints)

if __name__ == "__main__":
    main()

