// [Nasiha] COMMAND - abstract command.
// Receivers are non-owning Colleague* held by the concrete commands.
#ifndef COMMAND_H
#define COMMAND_H

class Command {
public:
    virtual ~Command() {}
    virtual void execute() = 0;
};
#endif
