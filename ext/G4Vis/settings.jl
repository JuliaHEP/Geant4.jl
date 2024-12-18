#----Visualization Settings------------------------------------------------------------------------
#    the format is a nested Julia NamedTuple (parsed directly from the program)
#    Note that with a single element in the tuple the user needs to append a "," 
#--------------------------------------------------------------------------------------------------
(
    display = (
        backgroundcolor =  :black,    # Display background color
        resolution = (1280, 720),     # Display resolution
        show_axis = true,             # Whether to show or not the axis
        camera_rotation = (0,0,0),    # Camera rotation
        camera_zoom = 1.0,            # Camera zoom
        ),
    trajectories = (
        color = :yellow,              # Color of the trajectories
    ),
    detector = (
        show_detector = true,         # Whether to draw the detector or not
    ),
)
