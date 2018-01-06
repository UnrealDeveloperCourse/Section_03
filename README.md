# Section_03
Building Escape


### Version Control 101

- Source Tree
- Git


### Ignoring Unreal Derived Files

- Derived files can be rebuilt
- code assets level layout cannot be rebuilt
- [treesize](https://www.jam-software.de/customers/downloadTrialProcess.php)
- [Unreal Directory Structure](https://docs.unrealengine.com/latest/INT/Engine/Basics/DirectoryStructure/)
- Binaries, Build, DerivedDataCache, Intermediate, Saved, directories all get rebuilt
- VC.db file gets rebuilt


### Your First .gitignore for Unreal

- Trying to load the solution in visual studio fails when Intermediate directory has been removed
- To fix, right click on the .uproject file in explorer and regenerate Visual Studio project files
- will create another Intermediate folder for you


### Getting to Know Unreal's Editor

- Create NewMap
- Set project settings to load NewMap as the default Editor Startup Map and Game Default Map


### Pointers Primer

- Memory Addresses
- Benefit: Saves you from moving things around in memory
- refer by reference instead of by value
- Disadvantage: You can lose control of data
- All three are the same
	+ `FActorComponentTickFunction* ThisTickFunction` <- Unreal standard
	+ `FActorComponentTickFunction * ThisTickFunction`
	+ `FActorComponentTickFunction *ThisTickFunction`
	+ "pointer" of type "FActor..."
- The -> Accessor Operator
	+ `AActor* SomeActor;`
	+ The `AActor` class has a method `GetName()`
	+ `*SomeActor` "de-references" the pointer
	+ You could write `(*SomeActor).GetName();`
	+ or `SomeActor->GetName()`
	+ [Pointers](http://www.cplusplus.com/doc/tutorial/pointers)


### Unreal's Class System

- ExploreClass Viewer
- In Content Browser Create a C++ Component called a PositionReport
- Visual Studio opens automatically
- In Project Description is where copyright information can be filled out


### Runtime Messages for Feedback

- `UE_LOG` log to Output Console
- Macro = "Unreal Header Tool Directive"
- All caps, Macro


### Accessing Object Names

- `GetOwner`
- `AActor*` pointer
- Use `->`
	+ equivalent to a `.` but looking up attributes of a pointer
- `GetName`
- `%s` for formatting
- `*` dereferencing
- `UE_LOG(YourLog,Warning,TEXT("MyCharacter's Name is %s"), *MyCharacter->GetName() );`
	- in this example `*` is not dereferencing, it is an overloaded operator because it is being used in a macro


### Include-What-You-Use for 4.17+ IWYU

- Not applicable, started the project in 4.18 which compiles without modifications


### Quiz

- We use blueprints instead of hardcoding object names so that UE will keep track of naming
- [Game Design Document](https://en.wikipedia.org/wiki/Game_design_document)
- "The purpose of a game design document is to unambiguously describe the game's selling points, target audience, gameplay, art, level design, story, characters, UI, assets, etc..."
- This course: Concept, Rules & Requirements
- ObjectName is an FString. Why do we have to use *ObjectName in our UE_LOG rather than just ObjectName?
	+ A: `UE_LOG` is expecting a TCHAR array, and the * effectively converts the string to this type.


### Getting Transforms in C++

- `FVector`
- `FString ObjectPos = GetOwner()->GetActorTransform().GetLocation().ToString();`


### Moving Objects with C++

- Temporary Actors
- Eject from the possessed pawn
- Snapping to the floor with End key
- `FRotator` struct to rep rotation
- `SetActorRotation()` to rotate objects
- Play -> Shift+F1 -> World Outliner -> View Options (bottom) -> Hide Temp Actors
- Create a Door Frame and Door
- Position them
- Make the Door Movable instead of Static
- Create a C++ Component on the Door
- Edit the code to add `GetOwner` and use `FRotator` to set rotations on the door


### Laying out Geometry

- BSP vs Static Meshes
	+ Binary Space Partitioning
	+ type Brush
	+ Old
	+ Not visible in the Modes tab in 4.18
- grid snap and quad view
- Alt+Drag translate to duplicate
- Hold L and double click for temp work Light


### Applying Materials

- self explanatory
- lots of help in Unreal tutorals


### Macros Starting with UPROPERY

- A macro is programmed cut-and-paste
- happens before code is compiled
- powerful functionality
- code completion is not hooked up by default
- obscure build errors can occur
- `ATriggerVolume`
- [VisibleAnywhere](https://docs.unrealengine.com/latest/INT/Programming/UnrealArchitecture/Reference/Properties/Specifiers/VisibleAnywhere/index.html)
- `UPROPERTY(EditAnywhere)`
- `ATriggerVolume* PressurePlate`
- New property now shows up on our OpenDoor Component
- duplicating object with the property set will associate the new object along with the PressurePlate settings


### Using Trigger Volumes

- `IsOverlappingActor()` on an `ATriggerVolume`
- Polling vs using events
- First, what Actor is going to do the triggering
- To test, play the game, eject, select the pawn and assign it to the Actor That Opens


### Unreal's Player Controller

- till now using `GetOwner()` to search "bottom up"
- now use `GetWorld()` to search "top down"
- Game Mode specifies the Default Pawn Class
- Default Pawn is your "body", is transient
- Player Controller is your "mind", persistent
- PlayerController method `GetPawn()`
- Project Settings -> Maps & Modes -> Default Modes -> BuildingEscape814GameMode


### Using Collision Volumes

- what collides with what
- tells physics engine what hits what
- trigger volume just triggers code
- a collider actually has physics simulated
- explore how to add collision volumes


### Using `GetTimeSeconds()`

- Play tunable
- refactor
- re-test
- [`GetWorld()->GetTimeSeconds()`](https://docs.unrealengine.com/latest/INT/API/Runtime/Engine/Engine/UWorld/GetTimeSeconds/index.html)
- 


### Grabbing System Overview

- Grabber.cpp Component to the Player
- Player is temp Actor, appears on play
- The Game Mode sets which Default Pawn to use
- Create Default Pawn and Game Mode Blueprint (easier no hard coding asset name)
- Specify our modified Default Pawn
- Project Settings -> Maps & Modes -> Default Modes -> Default Game Mode
- Will select our Blue Print Game Mode and Pawn Class
- Create a BP Pawn and add the Grabber Component to it
- Parameters of game play are set in Game Mode
- [Setting Up a Game Mode in Blueprints](https://docs.unrealengine.com/latest/INT/Gameplay/HowTo/SettingUpAGameMode/Blueprints/index.html)


### Modifying the Default Pawn Actor

- Blueprint templates
- Play, Eject, select Pawn, Blueprints -> Create Blueprint from Selected Pawn
- Details -> Add Component -> C++ Component -> Actor Component, call it Grabber
- Content Browser -> Open the Default Pawn Editor -> Add Component -> Custom -> Grabber
- Make an instance of Default Pawn and see that it has a Grabber Component


### Inherit Game Mode Blueprint

- DefaultPawn_BP is an asset
- we want o be able to track changes to its name
- Customize C++ Game Mode (chosen during inital Game Creation) with Blueprint
-  Select our new Default Pawn


### Getting Player Viewport

- Know where player is looking
- Out-parameters can be confusing
- A way of marking-up out parameters
- Continuously log out information
- [GetPlayerViewpoint](https://docs.unrealengine.com/latest/INT/API/Runtime/Engine/GameFramework/APlayerController/GetPlayerViewPoint/index.html)
- UE_LOG wants pointer to T CHARs not FStrings


### Using Draw Debug Line

x ----> b
^     +	
|   +	
| +	
a	

- Vector primer
	+ vector a ---->
	+ vector b ---->
	+ c = a + b
- Calculating `LineTraceEnd`
	+ Origin (0, 0, 0)
	+ `PlayerViewPointLocation`
		* Center of Player
	+ Need to convert our Rotation to Vector
	+ `LineTraceDirection = PlayerViewPointRotation.Vector()`
		* Unit Vector
		* First point of line
	+ Multiply by a Reach Vector to get the overall length of the line
	+ We have the 3 points of our equation


### Line Tracing AKA Ray Casting

- [Collision Filerting blog post](https://www.unrealengine.com/en-US/blog/collision-filtering)
- Add a table into the scene
- Most direct way of adding an object to the scene and make it a collision object is to select Simulate Physics in the Physics tab
	+ can give it a mass in kilos
	+ sets object "movable" on automatically
	+ sets Collision Presets to PhysicsActor
- Filter by object type
	+ Collisions type Physics Body
- Select the chair and click Simulate Physics
- Project Settings -> Engine -> Collision -> Object Channels
	+ Alternative Control


### `LineTraceSingleByObjectType()`

- [LineTraceSingleByObjectType](https://docs.unrealengine.com/latest/INT/API/Runtime/Engine/Engine/UWorld/LineTraceSingleByObjectType/)
- [FCollisionQueryParams](https://docs.unrealengine.com/latest/INT/API/Runtime/Engine/FCollisionQueryParams/index.html)
- Meet references `&`
- `LineTraceSingle` deprecated
- Build params inc. `FCollisionQueryParams`
- References
	+ Special pointers denoted by &
	+ Cannot be nullptr or null value
	+ Once assigned cannot be reassigned
	+ Think "alias"


### References & Pointers

- How references and pointers compare
- How to perform common operations in both
- What the `&` and `*` symbols mean in context
- Challenge: Repoint and Rewrite
- When to use references over pointers

- [An easier to understand explanation on pointers and references TUTORIAL](https://community.gamedev.tv/t/an-easier-to-understand-explanation-on-pointers-and-references-tutorial/10670)
	+ A Contrived Set of Examples:
	+ A pointer is a data type that "points" to another value stored in memory
	
	  name | value | address
	  -----|-------|--------
	  p    | 0003  | 0000
	       |       | 0001
	       |       | 0002
	  x    | 25    | 0003
	       |       | 0004

	+ assume: x is an int var, p is a int pointer (pointer capable of holding mem locations assoc. with int values)
	+ value stored in p is able to ref the mem location for the value of x
	+ if we are able to access the mem location for the value of x then we are able to access the value in that particular mem location
	+ might seem convoluted in this simple case
	+ in more complex cases we need pointers
	+ To declare a pointer, any of the examples will work
		* `int* p`; <- reads int pointer, p, slightly more legible
		* `int *p`; <- reads int, pointer p
		* `string* q`;
		* Follow the style guide you're working in
	+ & = Address of operator
		* Much like the id() function in Python <- Observation
	  
		  name | value | address
		  -----|-------|--------
	  -->      |       | 0000
		       |       | 0001
		       |       | 0002
		  x    | 25    | 0003 <--
		       |       | 0004

		* to get the "address of" x
			- `int* p = &x`; <- reads assign "address of" "x" to an "int pointer" "p"

		  name | value | address
		  -----|-------|--------
	      p    |-> 0003| 0000
		       |       | 0001
		       |       | 0002
		  x    | 25    | 0003
		       |       | 0004 <--

		* `cout << p << endl;`
			- 0003

	+ * = Contents of operator AKA dereference operator
		* Values stored at an address held by a pointer
			- `int* p = &x;`
			- `cout << *p << endl;` <- "dereference" "pointer p" "get the value assoc with the address"

		  name | value | address
		  -----|-------|--------
	      p    |-> 0003| 0000
		       |       | 0001
		       |       | 0002
		  x    | 25    | 0003
		       |       | 0004 <--

	+ *p is an alias for x
	+ every occurrance of x think of *p as another representation
		* `x = x + 5;` <- x occurs both on left/right of =
			- on the right reads "get the value stored at this particular memory location associated with x"
			- in other words **25**
			- on the left reads "store the result in a memory location specified by x"
			- when executed the result is 25 + 5, which is **30**

			  name | value | address
			  -----|-------|--------
		      p    |-> 0003| 0000
			       |       | 0001
			       |       | 0002
			  x    | 30    | 0003
			       |       | 0004 <--

		* `x = *p + 5;`
			- instead of getting the address which is what is actually stored in p, get the contents located at the memory location
			- when executed get the value stored 30 and add 5 then store it in the variable location specified by x

			  name | value | address
			  -----|-------|--------
		      p    |-> 0003| 0000
			       |       | 0001
			       |       | 0002
			  x    | 35    | 0003
			       |       | 0004 <--

		* `*p = *p + 5;`
			- dereferencing is happening on the left/right
			- deref of pointer p on the right gets the value 35
			- deref of pointer p on the left allows us to store a value at that designated location, *serving the exact same purpose as assigning to the veriable x*

			  name | value | address
			  -----|-------|--------
		      p    |-> 0003| 0000
			       |       | 0001
			       |       | 0002
			  x    | 40    | 0003
			       |       | 0004 <--
		* `cout << &*p << endl;`
			- `*p` same as getting the value of x
			- `&` getting the address of x (0003)
			- any time we see `&*` we can think of the operators as cancelling each other out
	+ How are pointers **Actually** used?
		* refer to new memory reserve during program execution
		* anytime we allocat more memory during the program execution, what gets returned is a pointer to the actual memory address
		* refer to large data structures without having to copy them
		* specify relationships between data items in data large structures
			- linked lists, trees, graphs, etc.
- Big difference between Pointers and References
	
		           | Pointers           | References
	---------------|--------------------|-----------
	memory address | Yes                | Yes
	re-assignment  | Yes                | No
	can be null    | Yes `nullptr`      | No (immutable)
	dref operator  | Yes `*p`           | No
	addr operator  | No  (IS an addr)   | Yes `&r`
	changing addr  | Yes `p = &y`       | No
	changing value | Yes `*p = x`       | Yes `r = x`

- The Contextual Meaning of `&` and `*` Symbols

	Context       | When Using                   | When Declaring
	--------------|------------------------------|---------------------------
	Code examples | `CopyOfActor =  *ActorPtr;`  | `UActor* ActorPtr;`
	              | `ActorAddr = &Actor;`        | `UActor &ActorRef;`
	--------------|------------------------------|---------------------------
	Symbol        | `*`          | `&`           | `*`        | `&`
	--------------|--------------|---------------|------------|--------------
	Syntax        | `*ActorPtr`  | `&Actor`      | `UActor*`  | `UActor&`
	--------------|--------------|---------------|------------|--------------
	Meaning       | Content at   | Addr of Actor | Pointer to | Reference to
				  | ActorPtr     |               | UActor     | UActor
	--------------|--------------|---------------|------------|--------------

- Pointers or References?
	+ ***Golden Rule: Use references unless you can't***
	+ References
		* newer and safer
		* In C there were only Pointers
	+ Pointers
		* provide back-compatibility
		* more powerful
		* very dangerous


### Resetting Your Unreal Project

- Unreal Solution keeps crashing
- Delete all temp files
- Order to reset
- Steps
	+ In SourceTree Check-out or Reset to a working commit
	+ Delete derived folders and files - leave Config, Content, and Source folders, and .uproject file
		* .vs, Binaries, Build, Intermediate, Saved, *.sln, VC.db
	+ Re-open Unreal - from the launcher or .uproject
		* re-creates *.generated.h files in Intermediate folder
	+ Generate your IDE project files
		* Right click .uproject -> Generate Project Files
		* Regen .dll and Intermediate


### Using `FindComponentByClass()`

- find attached Components
- `<>` for generics
- `nullptr` to initialize Pointers
- Log useful error if Component isn't attached


### Introducing Input Binding

- Settings -> Project Settings -> Input
- Action Mappings are used for on/off actions
- Axis Mappings are used for analog values
- You can give players a way to remap keys
- Many keys can bind to one action
- How to call a function on a key press or release

- Class Viewer -> ActorComponent -> Input Component
- Play Game -> Select Default Pawn in World Outliner -> Inspect Details -> PawnInputComponent
- Also during Gameplay inspect the DefaultPawn_BP components to find PawnInputComponent


### Accessors and Memory Layout

- How the arrow, dot and :: accessors work
- Introducing virtal memory
- Introducing permanent storage, stack & heap
- Head is also known as "free store"
- How accessor operators relate to memory
- Bind another input action

	+--------------+ 
	| Stack        |
	| ------------ |
	|      |       |
	|      X       | <- runtime
	|      |       |
	| ------------ |
	| Heap         |
	| ------------ |
	| Permanent    |
	| Storage      | <- compile time
	|              |
	+--------------+

	                   Left Term | Accessor | Examples
	+--------------+   ----------|----------|----------------
	| Stack        |   Instance  | .        | MyGrab.Grab()
	| ------------ |   Reference |          | MyBullCowCountStruct.Bulls
	|      |       |             |          | MyGrabRef.Grab()
	|      X       |   ----------|----------|----------------
	|      |       |   Pointer   | ->       | MyGrabPtr->Grab()
	| ------------ |             |          | MyGrabPtr->Reach
	| Heap         |             |          |         
	| ------------ |   ----------|----------|----------------
	| Permanent    |   Class,    | ::       | UGrabber::Grab
	| Storage      |   Enum,     |          | EWordStatus::OK
	|              |   Namespace |          | std::cout
	+--------------+                                  

- [Memory Layout of C Programs](http://www.geeksforgeeks.org/memory-layout-of-c-program/)


### Reducing Code in Hot Loops

- A "hot loop" is code that gets called often
- `TickComponent` is a good example, every frame
- Beware of code that you know will be called a lot
- Make it clear what happens every tick
- Refactor our code for speed
- Make it ready for the physics handle


### Using Physics Handles

- Red Green Refactor
	+ Red - not working, test failing
	+ Green - It's working (ugly ok)
	+ Refactor - Make it pretty (must still work)
- [UPhysicsHandleComponent](https://docs.unrealengine.com/latest/INT/API/Runtime/Engine/PhysicsEngine/UPhysicsHandleComponent/index.html)
- `GrabComponent()` No examples given in the documentation so run a find operation over the entire solution
- `GrabComponent` is deprecated, instead use:

```
GrabComponentAtLocationWithRotation
(
    UPrimitiveComponent * Component,
    FName InBoneName,
    FVector Location,
    FRotator Rotation
)
```

- implementation status is now Green


### Refactoring Rules

- Using multiple getters for multiple returns
- Less lines of clear code better (143 at start 115 end or %15 reduction)
- Naming is really important
- Comment the "why"
- The "what" should be obvious
- Might want to standardise first word of commit message as being 'refactor'
- Can create commit message before actually starting


### Introducting Unreal's TArray

- TArray Unreal's go to container class
- Can contain many elements of the same type
- We'll use to contain all actors on pressure plate
- Give our Default Pawn an eye-height and mass
	+ Select the Pawn and look in Details
	+ Set default eye height
	+ Select the collision component on the Pawn
	+ Check simulate physics
	+ give a mass in kg
	+ check simulation generates hit events
	+ and generate overlap events
- [GetOverLappingActors](https://docs.unrealengine.com/latest/INT/API/Runtime/Engine/GameFramework/AActor/GetOverlappingActors/1/index.html)
- [TArray](https://docs.unrealengine.com/latest/INT/Programming/UnrealArchitecture/TArrays/index.html)


### Iterating over `TArray` with `for`

- `auto&`
- `for (const auto& Iterator : Array)`
- find an actor's mass
- In Details for table and chair select Generate Overlap Events
- [UPrimitive to GetMass](https://docs.unrealengine.com/latest/INT/API/Runtime/Engine/Components/UPrimitiveComponent/index.html)
- * instead of & in this case
- [CppCon 2014: Scott Meyers "Type Deduction and Why You Care"](https://www.youtube.com/watch?v=wQxj20X-tIU)


### Debugging Game Issues

- Are you using source control
- You can "binary search" commits quite fast
	+ For example 1024 commits takes max 10 tries to find where problem started
	+ Halving the number of commits
	+ Check problem persists
	+ Half again if need be and repeat
- Think "what changed" and "possible side-effects"
- Remember you can eject using F8 during gameplay
- Pawn appears to be rolling
- Angular damping will stop it rolling quicker


### Managing Texture Tiling

- Material blueprint
- UV map


### Pointer Protection Process

- Horrible crashes result if we follow `nullptr`s
	+ Really bad if we follow something `undefined`
- Check pointers before use
- Always initialize Pointer to nullptr
- Example: deleting pressure plate in our game
- Example: Physics Handle removed from Default Pawn

```cpp
/*
	insert code like this at least once
  	in the most superficial level of the code as possible
*/
if (!PressurePlate) {
		UE_LOG(LogTemp, Error, TEXT("%s missing pressure plate"), *Owner->GetName())
}
```

```cpp
/// otherwise, just bail from any method that encounters nullptrs
if (!PressurePlate) {return;}
```


### Exposing Events to Blueprint

- Sometimes Blueprint is the better choice
- Example: defining our door swing as a curve
- Create an event called `OnOpenRequest`
- Using `UPROPERTY (BlueprintAssignable)*`
- [BlueprintAssignable](https://docs.unrealengine.com/latest/INT/Programming/UnrealArchitecture/Reference/Properties/Specifiers/BlueprintAssignable/index.html)
- Door Blueprint
- Convert selected Actor to Blueprint class
- Confirm Door has collision setup
- Going to add Timeline node in Event Graph

```cpp
// OpenDoor.h

/// Create a new class at the top

/// This is a macro that creates a new type
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOpenRequest);


/// inside Building Escape class make a new public declaration
UPROPERTY(BlueprintAssignable)
FOnOpenRequest OnOpenRequest;
```

```cpp
// OpenDoor.cpp

/// Create a broadcast event
void UOpenDoor::OpenDoor()
{
	// Owner->SetActorRotation(FRotator(0.f, OpenAngle, 0.f)); // Set the door rotation
	OnOpenRequest.Broadcast();
}
```

- Blueprint Editor
- Select OpenDoor component and right click in the Node Editor
- Add Event Dispatcher On Open Request
- Click and drag white line
- Create a Set Actor Rotation node (search is faster)


### Using Blueprint Timeline

- Setting rotation of the door in a Timeline
- OpenDoor Blueprint Editor
- Right click -> Add Timeline
- Double click it
- Add Float Track in Timeline
- Rename Timeline, rename track name
- Create keyframes
- Modify key tangents
- Connect output of On Open Request -> Door Swing (Timeline) Play
- Create a Make Rotator
- Connect output of Door Swing Open Angle -> Make Rotator Z (Yaw) -> Set Actor Rotation New Rotation
- Ctrl+Drag
- Connect output of Door Swing Update -> Set Actor Rotation Exec
- Running the game will compile the Blueprint automatically
- Toggle comment to view animation percentage


### Everything in its place

- `OnClose()`
- `TriggerMass`
- Create and Connect `OnClose`
	+ Rename the event class to `FDoorEvent`
	+ Rename `OnOpenRequest` to `OnOpen`
	+ Create new `BlueprintAssignable` event
	+ Call this event `OnClose`
	+ Wire `OnClose` to the reverse pin in Blueprint


### Using Variables in Blueprint

- Store rotation at start
- set relative rotation
- `BeginPlay` Node
- `GetActorRotation`
	+ time independant
	+ promote a variable
	+ Rename `New_Var_0` -> Initial Rotation
	+ Wire `BeginPlay` to the Set Node
- `SetActorRotation`
	+ `CombineRotators`
	+ Wire a `GetInitialRotation` into `CombineRotators` B pin


### Sound FX and Audio Clips

- Trigger a sound in Blueprint
- We'll use C++ later
- We'll always reference our assets via BP
- How to trigger a 3D sound

- `SoundAtLocation`
- Event Graph -> Create "Sound Timing" Timeline
- Set a key at frame .1 with value 0
- Door Swing node now has Sound Timing output pin
- Wire that pin into Play Sound At Location Exec pin
- Play sound emenating from the door location
- `GetActorLocation` Return Value into Play Sound At Location, Location pin


### Section 3 Wrap Up

- Finished!
