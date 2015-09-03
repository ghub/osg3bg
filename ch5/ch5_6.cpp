#include <osg/Switch>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

class AnimatingSwitch : public osg::Switch
{
public:
    AnimatingSwitch()
        : osg::Switch()
        , counter_(0)
    {
    }
    AnimatingSwitch(
        const AnimatingSwitch& copy,
        const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY)
            : osg::Switch(copy, copyop)
            , counter_(copy.counter_)
    {
    }
    META_Node(osg, AnimatingSwitch);

    virtual void traverse(osg::NodeVisitor& nv)
    {
        if (!((++counter_) % 60))
        {
            setValue(0, !getValue(0));
            setValue(1, !getValue(1));
        }
        osg::Switch::traverse(nv);
    }

protected:
    unsigned int counter_;
};

int main(
    int /*argc*/,
    char** /*argv*/)
{
    osg::ref_ptr<osg::Node> model1 = osgDB::readNodeFile("cessna.osg");
    osg::ref_ptr<osg::Node> model2 = osgDB::readNodeFile("cessnafire.osg");

    osg::ref_ptr<AnimatingSwitch> root = new AnimatingSwitch;
    root->addChild(model1.get(), true);
    root->addChild(model2.get(), false);

    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());
    return viewer.run();
}
