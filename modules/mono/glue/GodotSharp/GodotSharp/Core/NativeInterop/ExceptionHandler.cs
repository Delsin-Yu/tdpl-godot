using System;

namespace Godot.NativeInterop;

/// <summary>
/// Represents a type that's capable for handling application-wise exceptions.
/// </summary>
public interface IExceptionHandler
{
    /// <summary>
    /// Called when an exception has raised within the Godot invoked event methods.
    /// </summary>
    /// <param name="exception">The exception</param>
    /// <returns>true if this handler instance has successfully handled the exception, otherwise, false.</returns>
    bool TryHandleException(Exception exception);
}

/// <summary>
/// Allows developer customized exception handling logic.
/// </summary>
public static class ExceptionHandlers
{
    /// <summary>
    /// Sets the specified exception handler as the application exception handler
    /// </summary>
    /// <param name="handler">The handler instance</param>
    public static void SetExceptionHandler(IExceptionHandler handler)
    {
        Handler = handler;
    }

    internal static IExceptionHandler Handler;
}
