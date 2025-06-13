#----Callback structures---------------------------------------------------------------------------
mutable struct CallBackData{CONTEXT}
    context::CONTEXT
    callback::Function   # (i::Int32, ctx::T)::Int32
end

struct CallBack{CONTEXT}
    cfunction::CxxWrap.CxxWrapCore.SafeCFunction
    cbdata::CallBackData{CONTEXT}
end

#----Global vector (GC) ---------------------------------------------------------------------------
callbacks = Vector{CallBack}()

#----Function to create a callback avoiding the use of closures (ARM is not supporting closures)
#    We need to project with a lock the make_callback since it can be called from concurrent threads
const spinlock = Base.Threads.SpinLock()
const cb_counter = Ref(0)
function make_callback(ctx, fun, rt, args)
    lock(spinlock)
    try
        i_callback = Symbol(:_internal_callback_, "$(fun)_", cb_counter[])
        narg = Base.length(args)
        CONTEXT = typeof(ctx)
        #---create the internal callback function------------------------------------------------------
        if narg == 0
            eval( 
                quote
                    function $i_callback(data::Ptr{Cvoid})::$rt
                        cb_data = unsafe_pointer_to_objref(data)::CallBackData{$CONTEXT}
                        cb_data.callback(cb_data.context)
                    end
                end
            )
        elseif narg == 1
            eval( 
                quote
                    function $i_callback(a1::$(args[1]), data::Ptr{Cvoid})::$rt
                        cb_data = unsafe_pointer_to_objref(data)::CallBackData{$CONTEXT}
                        cb_data.callback(a1[], cb_data.context)
                    end
                end
            )
        elseif narg == 2
            eval( 
                quote
                    function $i_callback(a1::$(args[1]), a2::$(args[2]), data::Ptr{Cvoid})::$rt
                        cb_data = unsafe_pointer_to_objref(data)::CallBackData{$CONTEXT}
                        cb_data.callback(a1[], a2[], cb_data.context)
                    end
                end
            )
        else
            error("callbacks with more than 2 arguments not yet supported")
        end
        #---Instantiate the callback-------------------------------------------------------------------
        cb = eval(
                quote
                    CallBack{$CONTEXT}( @safe_cfunction($i_callback, $rt, ($(args...), Ptr{Cvoid})),
                                        CallBackData{$CONTEXT}($ctx, $fun))
                end
            )
        push!(callbacks, cb)
        unlock(spinlock)
        return cb
    catch
        unlock(spinlock)
        rethrow()
    end
end
function closure(cb::CallBack)
    return (cb.cfunction, pointer_from_objref(cb.cbdata))
end
function null_closure(rt, args)
    return (CxxWrap.CxxWrapCore.SafeCFunction(C_NULL, rt, [ args... ; Ptr{Cvoid}]), C_NULL)
end

