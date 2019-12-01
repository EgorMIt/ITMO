package quality;

public abstract class AbstractQuality implements QualityAble {
    public String qualityName;
    public String typeName;


    @Override
    public int hashCode() {
        return super.hashCode()+this.getPlace().hashCode();
    }

    @Override
    public boolean equals(Object obj) {
        return obj.hashCode() == this.hashCode();
    }

    @Override
    public String toString() {
        return "Качество " + this.getQuality();
    }

    public String getPlace() {
        return qualityName;
    }
}
