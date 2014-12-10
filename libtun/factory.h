#pragma once

namespace xTunnel
{
    template <typename T>
    class Factory
    {
    public:
        typedef T ItemType;
        typedef shared_ptr<T> ItemPtr;
        typedef shared_ptr<Factory> FactoryPtr;

    private:
        template <typename TItem, typename TBase = TItem>
        class PointerFactory : public Factory<TBase>
        {
        public:
            virtual ~PointerFactory() {  }

            virtual ItemPtr Create() const
            {
                return make_shared<TItem>();
            }
        };

    public:
        template <typename TItem>
        static FactoryPtr Subclass()
        {
            return make_shared<PointerFactory<TItem, T>>();
        }

        virtual ~Factory() = 0 {  }
        virtual ItemPtr Create() const = 0;
    };
}