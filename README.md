# FM2K Rollback Issues Overview
This little document should outline some issues with 100% rollback compatibility with ALL FM2K games as they're different in their own way and what can be done to prevent issues on the baseline system proposed in this document. I hope this document can help with the efforts for FM2K rollback support.
# FM2K games in general, a basic overview
As we know, FM2K games have bugs, especially the one where elements on-screen disappear after pausing or tabbing out, this would more than likely affect rollback because memory will be different per client. This is a rudimentary regurgitation of the information.
Some FM2K games have different files associated with them, like in the case of Fighting is Magic: Tribute Edition, it requires Microsoft Visual C++ 2010 Redistributable x86 and a custom DLL (Hories.dll), this needs to be taken into consideration.
Fighting is Magic: Tribute Edition-style builds have the stages in one file which is about 500 MB, up to 800 MB if you’re talking about the later games. This can pose an issue for writing save states on the fly due to the memory allocation that the engine is pushing. Heavy optimisation would be needed.
# Let’s talk about saving the ENTIRE game state, graphics and sounds included, everything in memory at once.
## Simulation Overhead & State Management
Rollback netcode requires each game to simulate multiple frames which can cause high CPU usage in older CPUs, my personal baseline for optimisation is the Intel Core i5-3320M from 2012. In addition, storing a history of game states can introduce more CPU usage and memory usage.
## Memory Consumption
When talking about rollback you need state storage which can increase memory usage. The issue with this isn’t the act of state storage itself, it’s the fact that many pre-built computers still only come with 8 GB of memory or less. This is obviously an issue when we’re talking about the fact that some FM2K games use 500 MB+ of active memory at one time. It’s worth taking it into consideration. In addition, buffer size is also a memory hog on top of the already 500 MB we’re writing and reading from memory. This will cause stuttering if it’s not optimised or addressed properly, especially on older systems with DDR3 memory.
## Optimisation
With my baseline being an Intel Core i5-3320M from the Ivy Bridge generation of Intel CPUs, this CPU runs at 2.6 GHz base speed with a 3.3 GHz single core boost clock, it has 2 physical cores and 4 threads meaning it’s hyperthreaded. It also has Intel SpeedStep technology which “predicts” what calculation to make next to help processing speed. It’s worth noting that SpeedStep got disabled on a lot of Intel CPUs after the Spectre and Meltdown fiasco. This can cause more performance issues so optimisation for these older CPUs is key.
## Hardware Viability
You need to make sure in any application or game that you target the people on weaker hardware as they will have a bad experience otherwise. This is more of warning to anyone taking on this task as making your application and in extension netcode only run on systems with more than 2 cores and 4 threads is a bit silly considering most new cheaper laptops (~£200) still only come with Intel Celerons and AMD Athlons with 2 cores and 4 threads. Even though these CPUs are much more powerful than my baseline, they will still have limited resources. Another thing to think about when discussing hardware viability is memory and most cheap laptops only have 8 GB or less. This is still the case in 2025.
## So what would happen if you saved the ENTIRE game state every 10ms
It would be unfeasible for any computer to pull off.
# Okay, so what about just saving logic and variables?
It’s plausible. But someone’s concern was that since the game engine runs at 100 FPS (supposedly; we still don’t have confirmation on that) it needs to resimulate skipped frames which means it might have to resimulate around 20 logic frames in 1/10th of a second.
## Extra info
I will eventually write the next part of this which will involve how feasible it would be to only save logic and variables, detached from the rendering process and how it would fair on the baseline system.
# What don’t we need to talk about?
-	Network; this doesn’t apply to this document as this is mostly about hardware issues. Network is a completely different kettle of fish.
-	Visual artifacts; also, not in the scope of this document. Unless memory errors cause them in which case, oh no.
# Conclusion
While it is possible to implement rollback in FM2K through various means, the question more becomes if it’s worth the time and effort? Would people really want to spend upwards of 16 months on this project? Only time will tell. I personally expect 100% compatibility as typical rollback only rolls back logic and variables. I will be keeping a close eye on these developments and will test to the fullest extent if it ever gets released as anything noteworthy. The baseline system I have talked about in this document is going to be the machine for my tests, if it runs poorly, it is not ready for the poverty area of the fighting game community.

If there's anything I've missed, be sure to leave an (issue)[https://github.com/windowslogic/fm2k-rollback-issues/issues]
