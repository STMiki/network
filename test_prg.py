

from tkinter import *
import sys

if (__name__ == '__main__'):
    if (len(sys.argv[1:]) != 2):
        print("Usage: {} file_name function_name".format(sys.argv[0]))
        sys.exit()
    else:
        prg = sys.argv[1]
        fnc = sys.argv[2]
        if (prg.endswith(".py")):  prg = prg[:-3]
        instance = __import__(prg, fromlist=[fnc])
        print(instance)
        globals()[fnc] = eval("instance.{}".format(fnc))
    main = Tk()
    main.title("fenetre de selection de monde")
    top = Toplevel(main)
    top.title("Labyrinthe de c'est mor")
    StartGame(3, 2, top)
    main.mainloop()
